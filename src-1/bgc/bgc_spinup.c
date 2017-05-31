#include "pihm.h"

void BGCSpinup (char *simulation, pihm_struct pihm, char *outputdir)
{
    FILE           *soilc_file;
    FILE           *vegc_file;
    FILE           *spinyr_file;
    FILE           *restart_file;
    FILE           *sminn_file;
    char            fn[MAXSTRING];
    char            restart_fn[MAXSTRING];
    int             i, j;
    struct tm      *timestamp;
    int             metyr;
    int             t;
    int             first_balance = 1;
    int             metyears;
    int            *steady1, *steady2;
    int            *rising;
    int             metcycle = 0;
    int             spinyears = 0;
    double         *tally1, *tally1b;
    double         *tally2, *tally2b;
    double          t1;
    int            *spinup_complete;
    int            *spinup_year;
    int             total_complete;
    //double         *naddfrac;

    timestamp = (struct tm *)malloc (sizeof (struct tm));

    steady1 = (int *)malloc (pihm->numele * sizeof (int));
    steady2 = (int *)malloc (pihm->numele * sizeof (int));
    rising = (int *)malloc (pihm->numele * sizeof (int));

    spinup_complete = (int *)malloc (pihm->numele * sizeof (int));
    spinup_year = (int *)malloc (pihm->numele * sizeof (int));

    tally1 = (double *)malloc (pihm->numele * sizeof (double));
    tally1b = (double *)malloc (pihm->numele * sizeof (double));
    tally2 = (double *)malloc (pihm->numele * sizeof (double));
    tally2b = (double *)malloc (pihm->numele * sizeof (double));

    //naddfrac = (double *)malloc (pihm->numele * sizeof (double));

    metyears = pihm->ctrl.spinupendyear - pihm->ctrl.spinupstartyear + 1;
    metyr = 0;

    spinyears = 0;
    metcycle = 0;

    for (i = 0; i < pihm->numele; i++)
    {
        spinup_complete[i] = 0;
        steady1[i] = 0;
        steady2[i] = 0;
        rising[i] = 1;
    }

    do
    {
        if (metcycle == 0)
        {
            for (i = 0; i < pihm->numele; i++)
            {
                tally1[i] = 0.0;
                tally1b[i] = 0.0;
                tally2[i] = 0.0;
                tally2b[i] = 0.0;
            }
        }

        if (metyr == metyears)
        {
            metyr = 0;
        }

        PIHMprintf (VL_NORMAL, "Year: %6d\n", spinyears);

        for (j = 0;
            j < (pihm->ctrl.spinupend - pihm->ctrl.spinupstart) / 24 / 3600;
            j++)
        {
            t = pihm->ctrl.spinupstart + (j + 1) * 24 * 3600;

            //for (i = 0; i < pihm->numele; i++)
            //{
            //    naddfrac[i] = 1.0;

            //    if (!steady1[i] && rising[i] && metcycle == 0)
            //    {
            //        naddfrac[i] = 1.0 - ((double) j / (double) metyears / 365.0);
            //    }
            //    else
            //    {
            //        naddfrac[i] = 0.0;
            //    }

            //    naddfrac[i] = 0.0;
            //}

            DailyBgc (pihm, t, pihm->ctrl.spinupstart, first_balance);

            first_balance = 0;

            for (i = 0; i < pihm->numele; i++)
            {
                if (metcycle == 1)
                {
                    tally1[i] += pihm->elem[i].summary.soilc;
                    tally1b[i] += pihm->elem[i].summary.totalc;
                }
                if (metcycle == 2)
                {
                    tally2[i] += pihm->elem[i].summary.soilc;
                    tally2b[i] += pihm->elem[i].summary.totalc;
                }
            }
        }

        metyr++;

        spinyears = spinyears + j / 365;

        for (i = 0; i < pihm->numele; i++)
        {

            if (!steady1[i] && metcycle == 2)
            {
                /* convert tally1 and tally2 to average daily soilc */
                tally1[i] /= (double)metyears *365.0;
                tally2[i] /= (double)metyears *365.0;
                rising[i] = (tally2[i] > tally1[i]);
                t1 = (tally2[i] - tally1[i]) / (double)metyears;
                steady1[i] = (fabs (t1) < SPINUP_TOLERANCE);
            }
            /* second block is after supplemental N turned off */
            else if (steady1[i] && metcycle == 2)
            {
                /* convert tally1 and tally2 to average daily soilc */
                tally1[i] /= (double)metyears *365.0;
                tally2[i] /= (double)metyears *365.0;
                t1 = (tally2[i] - tally1[i]) / (double)metyears;
                steady2[i] = (fabs (t1) < SPINUP_TOLERANCE);

                /* if rising above critical rate, back to steady1=0 */
                if (t1 > SPINUP_TOLERANCE)
                {
                    steady1[i] = 0;
                    rising[i] = 1;
                }
            }

            if (steady1[i] && steady2[i])
            {
                if (spinup_complete[i] == 0)
                {
                    PIHMprintf (VL_NORMAL,
                        "Ele %d spinup %d Avg daily soilc = %lf (%lf)\n", i,
                        steady1[i] && steady2[i], tally1[i],
                        pihm->elem[i].summary.soilc);
                    spinup_year[i] = spinyears;
                }
                spinup_complete[i] = 1;
            }
        }

        if (metcycle == 2)
        {
            metcycle = 0;
        }
        else
        {
            metcycle++;
        }

        total_complete = 0;
        for (i = 0; i < pihm->numele; i++)
        {
            total_complete += spinup_complete[i];
        }

        PIHMprintf (VL_NORMAL,
            "%d elements completed spin-up, %d elements to go\n",
            total_complete, pihm->numele - total_complete);

        /* spinup control */
        /* if this is the third pass through metcycle, do comparison */
        /* first block is during the rising phase */

        /* end of do block, test for steady state */
    } while (spinyears < pihm->ctrl.maxspinyears || metcycle != 0);     // || total_complete < PIHM->NumEle);

    sprintf (fn, "%ssoilc.dat", outputdir);
    soilc_file = fopen (fn, "w");

    sprintf (fn, "%svegc.dat", outputdir);
    vegc_file = fopen (fn, "w");

    sprintf (fn, "%sspinyr.dat", outputdir);
    spinyr_file = fopen (fn, "w");

    sprintf (fn, "%ssminn.dat", outputdir);
    sminn_file = fopen (fn, "w");

    sprintf (restart_fn, "input/%s/%s.bgcic", simulation, simulation);
    restart_file = fopen (restart_fn, "wb");
    for (i = 0; i < pihm->numele; i++)
    {
        RestartOutput (&pihm->elem[i].cs, &pihm->elem[i].ns,
            &pihm->elem[i].epv, &pihm->elem[i].restart_output);
        fwrite (&(pihm->elem[i].restart_output), sizeof (bgcic_struct), 1,
            restart_file);
        fprintf (soilc_file, "%lf\t", pihm->elem[i].summary.soilc);
        fprintf (vegc_file, "%lf\t", pihm->elem[i].summary.vegc);
        fprintf (spinyr_file, "%d\t", spinup_year[i]);
        fprintf (sminn_file, "%lf\t", pihm->elem[i].ns.sminn);
    }
    for (i = 0; i < pihm->numriv; i++)
    {
        fwrite (&pihm->riv[i].ns.sminn, sizeof (double), 1, restart_file);
        fprintf (sminn_file, "%lf\t", pihm->riv[i].ns.sminn);
    }

    fclose (sminn_file);
    fclose (soilc_file);
    fclose (vegc_file);
    fclose (restart_file);
    fclose (spinyr_file);

    free (steady1);
    free (steady2);
    free (rising);
    free (spinup_complete);
    free (spinup_year);
    free (tally1);
    free (tally1b);
    free (tally2);
    free (tally2b);
    //free (naddfrac);
}

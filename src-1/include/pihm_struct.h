#ifndef PIHM_STRUCT_HEADER
#define PIHM_STRUCT_HEADER

#ifdef _BGC_

/*****************************************************************************
 * A structure to hold information on the annual co2 concentration
 * ---------------------------------------------------------------------------
 * Variables                Type        Description
 * ==========               ==========  ====================
 * varco2                   int         0 = const 1 = use file
 * co2ppm                   double      constant CO2 concentration [ppm]
 ****************************************************************************/
typedef struct co2control_struct
{
    int             varco2;
    double          co2ppm;
} co2control_struct;

/*****************************************************************************
 * A structure to hold annual nitrogen deposition data
 * ---------------------------------------------------------------------------
 * Variables                Type        Description
 * ==========               ==========  ====================
 * varndep                  int         0 = const 1 = use file
 * ndep                     double      wet+dry atmospheric deposition of N
 *                                        [kgN m-2 yr-1]
 * nfix                     double      symbiotic+asymbiotic fixation of N
 *                                        [kgN m-2 yr-1]
 ****************************************************************************/
typedef struct ndepcontrol_struct
{
    int             varndep;
    double         *ndep_array;
    int            *ndepyear_array;
    int             ndepvals;
    double          ndep;
    double          nfix;
} ndepcontrol_struct;
#endif

/*****************************************************************************
 * Global calibration coefficients
 * ---------------------------------------------------------------------------
 * Variables                Type        Description
 * ==========               ==========  ====================
 * ksath                    double      calibration coefficient [-]
 * ksatv                    double      calibration coefficient [-]
 * kinfv                    double      calibration coefficient [-]
 * kmach                    double      calibration coefficient [-]
 * kmacv                    double      calibration coefficient [-]
 * dinf                     double      calibration coefficient [-]
 * rzd                      double      calibration coefficient [-]
 * dmac                     double      calibration coefficient [-]
 * porosity                 double      calibration coefficient [-]
 * alpha                    double      calibration coefficient [-]
 * beta                     double      calibration coefficient [-]
 * areafv                   double      calibration coefficient [-]
 * areafh                   double      calibration coefficient [-]
 * vegfrac                  double      calibration coefficient [-]
 * albedo                   double      calibration coefficient [-]
 * rough                    double      calibration coefficient [-]
 * ec                       double      calibration coefficient [-]
 * ett                      double      calibration coefficient [-]
 * edir                     double      calibration coefficient [-]
 * rivrough                 double      calibration coefficient [-]
 * rivksath                 double      calibration coefficient [-]
 * rivksatv                 double      calibration coefficient [-]
 * rivbedthick              double      calibration coefficient [-]
 * rivdepth                 double      calibration coefficient [-]
 * rivshpcoeff              double      calibration coefficient [-]
 * prcp                     double      multiplier of precipitation [-]
 * sfctmp                   double      offset of surface air temperature [K]
 * ---------------------------------------------------------------------------
 * Variables below only used in Flux-PIHM
 * ---------------------------------------------------------------------------
 * smcref                   double      calibration coefficient[-]
 * smcwlt                   double      calibration coefficient[-]
 * rsmin                    double      calibration coefficient[-]
 * drip                     double      calibration coefficient[-]
 * cmcmax                   double      calibration coefficient[-]
 * czil                     double      calibration coefficient[-]
 * fxexp                    double      calibration coefficient[-]
 * cfactr                   double      calibration coefficient[-]
 * rgl                      double      calibration coefficient[-]
 * hs                       double      calibration coefficient[-]
 * ---------------------------------------------------------------------------
 * Variables below only used in RT-Flux-PIHM
 * ---------------------------------------------------------------------------
 * pco2                     double      calibration coefficient[-]
 * keq                      double      calibration coefficient[-]
 * ssa                      double      calibration coefficient[-]
 * site_den                 double      calibration coefficient[-]
 * prep_conc                double      calibration coefficient[-]
 ****************************************************************************/
typedef struct calib_struct
{
    double          ksath;
    double          ksatv;
    double          kinfv;
    double          kmach;
    double          kmacv;
    double          dinf;
    double          rzd;
    double          dmac;
    double          porosity;
    double          alpha;
    double          beta;
    double          areafv;
    double          areafh;
    double          vegfrac;
    double          albedo;
    double          rough;
    double          ec;
    double          ett;
    double          edir;
    double          rivrough;
    double          rivksath;
    double          rivksatv;
    double          rivbedthick;
    double          rivdepth;
    double          rivshpcoeff;
    double          prcp;
    double          sfctmp;
#ifdef _NOAH_
    double          smcref;
    double          smcwlt;
    double          rsmin;
    double          drip;
    double          cmcmax;
    double          czil;
    double          fxexp;
    double          cfactr;
    double          rgl;
    double          hs;
#endif
#ifdef _RT_
    double          pco2;
    double          keq;
    double          ssa;
    double          site_den;
    double          prep_conc;
#endif
} calib_struct;

/*****************************************************************************
 * Model control parameters
 * ---------------------------------------------------------------------------
 * Variables                Type        Description
 * ==========               ==========  ====================
 * ascii                    int         flag to turn on ascii output
 * Tecplot                  int         flag to turn on Tecplot output
 * write_ic                 int         flag to write model output at the last
 *                                        time step as initial conditions
 * solver                   int         solver type
 * nstep                    int         number of external time steps (when
 *                                        results can be printed) for the
 *                                        whole simulation
 * nprint                   int         number of variables for output
 * nprintT                  int         number of variables for Tecplot output
 * prtvrbl                  int[]       time interval to output average values
 *                                        of variables; 0=turn off output
 * init_type                int         initialization mode:
 *                                        0=relaxed mode, 1=use .ic file
 * unsat_mode               int         unsaturation formulation:
 *                                        1=kinematic, 2=diffusion
 * surf_mode                int         surface overland flow formulation:
 *                                        1=kinematic, 2=diffusion
 * riv_mode                 int         river routing formulation:
 *                                        1=kinematic, 2=diffusion
 * abstol                   double      absolute tolerance [m]
 * reltol                   double      relative tolerance [-]
 * initstep                 double      initial step size [s]
 * maxstep                  double      maximum step size [s]
 * etstep                   double      land surface (ET) time step [s]
 * starttime                int         start time of simulation [ctime]
 * endtime                  int         end time of simulation [ctime]
 * stepsize                 int         model step size [s]
 * tout                     int*        model output times [ctime]
 * ---------------------------------------------------------------------------
 * Variables below only used in Flux-PIHM
 * ---------------------------------------------------------------------------
 * nsoil                    int         number of standard soil layers
 * sldpth                   double[]    thickness of soil layer [m]
 * rad_mode                 int         radiation forcing mode:
 *                                        0=uniform, 1=topographic
 * ---------------------------------------------------------------------------
 * Variables below only used in Flux-PIHM-BGC
 * ---------------------------------------------------------------------------
 * simstarttime             double      start time of BGC simulation
 * simendtime               double      end time of BGC simulation
 * bgc_spinup               int         flag: 1=spinup run, 0=normal run
 * maxspinyears             int         maximum number of years for spinup run
 * read_restart             int         flag to read BGC restart file
 * write_restart            int         flag to write BGC restart file
 * spinupstartyear          int         first met year for BGC spinup
 * spinupendyear            int         last met year for BGC spinup
 * spinupstart              int         start time of BGC spinup [ctime]
 * spinupend                int         end time of BGC spinup [ctime]
 * cs                       cstate_struct
 *                                      carbon state for initialization
 * ns                       nstate_struct
 *                                      nitrogen state for initialization
 * cinit                    cinit_struct
 *                                      carbon initialization parameters
 ****************************************************************************/
typedef struct ctrl_struct
{
    int             ascii;
	int             tecplot;
	int				cvode_perf;
	int				waterB;
    int             write_ic;
    int             solver;
    int             nstep;
    int             nprint;
	int             nprintT;
    int             prtvrbl[MAXPRINT];
    int             init_type;
    int             unsat_mode;
    int             surf_mode;
    int             riv_mode;
    double          abstol;
    double          reltol;
    double          initstep;
    double          maxstep;
    int             etstep;
    int             starttime;
    int             endtime;
    int             stepsize;
    int            *tout;
#ifdef _NOAH_
    int             nsoil;
    double          sldpth[MAXLYR];
    int             rad_mode;
#endif
#ifdef _BGC_
    int             simstarttime;
    int             simendtime;
    int             bgc_spinup;
    int             maxspinyears;
    int             read_restart;
    int             write_restart;
    int             spinupstartyear;
    int             spinupendyear;
    int             spinupstart;
    int             spinupend;
    cstate_struct   cs;
    nstate_struct   ns;
    cinit_struct    cinit;
#endif
} ctrl_struct;

/*****************************************************************************
 * Print control structure
 * ---------------------------------------------------------------------------
 * Variables                Type        Description
 * ==========               ==========  ====================
 * name                     char[]      name of output file
 * intvl                    int         output interval [s]
 * nvar                     int         number of variables for print
 * var                      double**    pointers to model variables
 * buffer                   double*     buffer for averaging variables
 ****************************************************************************/
typedef struct prtctrl_struct
{
    char            name[MAXSTRING];
    int             intvl;
    int             nvar;
    double        **var;
    double         *buffer;
} prtctrl_struct;

/*****************************************************************************
* Tecplot print control structure
* ---------------------------------------------------------------------------
* Variables                Type        Description
* ==========               ==========  ====================
* name                     char[]      name of output file
* intvl                    int         output interval [s]
* intr                     int         river identifier 
* nvar                     int         number of variables for print
* var                      double**    pointers to model variables
* x, y, z                  double**    pointers to model coordinates 
* nnodes                   int         number of nodes
* buffer                   double*     buffer for averaging variables
****************************************************************************/
typedef struct prtctrlT_struct
{
	char            name[MAXSTRING];
	int             intvl;
	int             intr;
	int             nvar;
	double        **var;
	double        **x, **y, **zmax, **zmin;
	int             nnodes;
	int           **node0, **node1, **node2;
	double         *buffer;
} prtctrlT_struct;

/*****************************************************************************
 * Print control structure
 * ---------------------------------------------------------------------------
 * Variables                Type        Description
 * ==========               ==========  ====================
 * numele                   int         number of triagular elements
 * numriv                   int         number of river segments
 * longitude                double      domain logitude
 * latitude                 double      domain latitude
 * elevation                double      average domain elevation
 ****************************************************************************/
typedef struct pihm_struct
{
    int             numele;
    int             numriv;
    double          longitude;
    double          latitude;
    double          elevation;
    filename_struct filename;
    meshtbl_struct  meshtbl;
    atttbl_struct   atttbl;
    soiltbl_struct  soiltbl;
    geoltbl_struct  geoltbl;
    lctbl_struct    lctbl;
    rivtbl_struct   rivtbl;
    shptbl_struct   shptbl;
    matltbl_struct  matltbl;
#ifdef _NOAH_
    noahtbl_struct  noahtbl;
#endif
#ifdef _CYCLES_
    agtbl_struct    agtbl;
    croptbl_struct  croptbl;
    mgmttbl_struct  mgmttbl;
#endif
#ifdef _BGC_
    co2control_struct co2;
    ndepcontrol_struct ndepctrl;
    epctbl_struct   epctbl;
#endif
    forc_struct     forc;
    elem_struct    *elem;
    river_struct   *riv;
    calib_struct    cal;
    ctrl_struct     ctrl;
    prtctrl_struct  prtctrl[MAXPRINT];
	prtctrlT_struct prtctrlT[MAXPRINT];
} *pihm_struct;
#endif

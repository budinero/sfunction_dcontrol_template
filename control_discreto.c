/*  Funciones de control de motores en C
*   Facundo Aguilera
*   2021
*/

#include "control_discreto_top.h"

#ifndef S_FUNCTION_NAME
#define S_FUNCTION_NAME control_discreto
#endif

#define S_FUNCTION_LEVEL 2

#include "simstruc.h" 
#include "types.h"

/*====================*
 * S-function methods *
 *====================*/

/* Function: mdlInitializeSizes ===============================================
 * Entradas, salidas estados
 */
static void mdlInitializeSizes(SimStruct *S)
{
    /* Parámetros */
    ssSetNumSFcnParams(S, 0);  /* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return; /* Parameter mismatch will be reported by Simulink */
    }

    /* Estados */
    ssSetNumContStates(S, 0);   // Número de estados continuos
    ssSetNumDiscStates(S, 0);   // Número de estados discretos

    /* Entradas */
    if (!ssSetNumInputPorts(S, 1)) return; // Número de puertos entrada
    ssSetInputPortWidth(S, 0, INPUT_WIDTH);           // Tamaño de puerto 0
    ssSetInputPortDirectFeedThrough(S, 0, 1); // Puerto 0 FeedThrough '1'
    ssSetInputPortRequiredContiguous(S, 0, true); /*direct input signal access*/

    /* Salidas */
    if (!ssSetNumOutputPorts(S, 1)) return; // Número de puertos salida
    ssSetOutputPortWidth(S, 0, OUTPUT_WIDTH); // Tamaño de puerto 0

    /* Tiempos de muestreo, para multirate */
    ssSetNumSampleTimes(S, 1);

    /* Vectores de trabajo (?) */
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    /* Opciones */
    ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_DISCRETE_VALUED_OUTPUT);
}



/* Function: mdlInitializeSampleTimes =========================================
 *    Specify the sample time as 1.0
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
    ssSetModelReferenceSampleTimeDefaultInheritance(S);      
}

#define MDL_INITIALIZE_CONDITIONS
/* Function: mdlInitializeConditions ========================================
 * Abstract:
 *    Initialize both discrete states to one.
 */
static void mdlInitializeConditions(SimStruct *S)
{
    initial();
}



/* Function: mdlOutputs =======================================================
 * Abstract:
 *      y = Cx + Du 
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    real_T          *y    = ssGetOutputPortRealSignal(S,0);
    const real_T    *u       = (const real_T*) ssGetInputPortSignal(S,0);
 
    UNUSED_ARG(tid); /* not used in single tasking mode */

    periodic( y, u);
}



//#define MDL_UPDATE
/* Function: mdlUpdate ======================================================
 * Abstract:
 *      xdot = Ax + Bu
 */
/*
static void mdlUpdate(SimStruct *S, int_T tid)
{
    real_T          *x       = ssGetRealDiscStates(S);
    const real_T    *u       = (const real_T*) ssGetInputPortSignal(S,0);

    UNUSED_ARG(tid); 
}
*/


/* Function: mdlTerminate =====================================================
 *    No termination needed, but we are required to have this routine.
 */
static void mdlTerminate(SimStruct *S)
{
    UNUSED_ARG(S); /* unused input argument */
}

// Finalización  ==============================================================
#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
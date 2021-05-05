
#include "control_discreto_top.h"

static int32_t contador;

/* Rutina inicial =============================================================
*/
void initial(void)
{
    contador = 0;
}

/* Rutina periódica ===========================================================
*/
void periodic(real_T *y, const real_T *u)
{   
    //*************************************************************************
    // Entradas
    bool sentido;
    bool habilitado;

    sentido     = (bool) u[0];
    habilitado  = (bool) u[1];
    

    //*************************************************************************
    // Proceso

    if (habilitado == true)
    {
        if (sentido == true)
            contador++;
        else
            contador--;
    }

    //********************************************
    // Salidas
    y[0] = sentido;
    y[1] = habilitado;
    y[2] = contador;
}

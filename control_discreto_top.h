#ifndef CONTROL_DISCRETO_TOP_H
#define CONTROL_DISCRETO_TOP_H

#include "types.h"


//***********************************************
// Opciones
#define S_FUNCTION_NAME control_discreto
#define INPUT_WIDTH     2
#define OUTPUT_WIDTH    3
#define SAMPLE_TIME     0.0001
//***********************************************

void initial(void);
void periodic(real_T *y, const real_T *u);


#endif //CONTROL_DISCRETO_TOP_H
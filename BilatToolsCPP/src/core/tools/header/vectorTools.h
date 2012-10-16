#ifndef VECTOR_TOOLS_H_
#define VECTOR_TOOLS_H_

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

void addVector(int* tabSum, int* tab1, int* tab2, int n);
void addVector(float* tabSum, float* tab1, float* tab2, int n);

float sum(float* ptrTab, int n);
void incrementer(int* ptrv, int n, int delta);
double norme(double* ptrTab, int n);
long dotProd(int* v1, int* v2, int n);

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


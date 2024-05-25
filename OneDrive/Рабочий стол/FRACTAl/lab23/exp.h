#ifndef EXP_H_INCLUDED
#define EXP_H_INCLUDED

#include "operations.h"

Matrix* matrix_power(const Matrix* A, int power, Matrix* res);

Matrix* matrix_exponential(const Matrix *A, double eps);

#endif // EXP_H_INCLUDED

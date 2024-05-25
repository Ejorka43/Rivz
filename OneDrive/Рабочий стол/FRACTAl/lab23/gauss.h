#ifndef GAUSS_H_INCLUDED
#define GAUSS_H_INCLUDED

#include "operations.h"

Matrix* inverse_matrix(const Matrix *m);

Matrix* solve_system(const Matrix* A, const Matrix* B, Matrix* x);

#endif // GAUSS_H_INCLUDED

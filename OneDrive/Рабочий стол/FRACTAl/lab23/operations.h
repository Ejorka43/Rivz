#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

#include "struct.h"

Matrix* matrix_add(Matrix* m1, const Matrix* m2);

Matrix* matrix_sum(Matrix* m, const Matrix* m1, const Matrix* m2);

Matrix* matrix_multiply_scalar(Matrix* matrix, double scalar);

Matrix* matrix_multiply(const Matrix* m1, const Matrix* m2);

Matrix* matrix_transpose_simple(Matrix* matrix);

Matrix* matrix_transpose(const Matrix* matrix, Matrix* result);

Matrix* multiply_row(Matrix* matrix, double scalar, size_t row);

Matrix* add_strings(Matrix* matrix, size_t row1, size_t row2);

Matrix* add_multiply_row_by_scalar(Matrix* m, size_t k, size_t t, double scalar);

Matrix* permute_string(Matrix* matrix, size_t row1, size_t row2);

double max_row_norm(const Matrix* matrix);

double max_col_norm(const Matrix* matrix);

Matrix* allocate_submatrix(const Matrix* matrix, size_t excluding_row, size_t excluding_col, Matrix* submatrix);

double matrix_determinant(const Matrix* mat);

#endif // OPERATIONS_H_INCLUDED

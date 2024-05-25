#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED
#include <stddef.h>
typedef struct {
    double* data;
    size_t rows;
    size_t cols;
} Matrix;

Matrix* matrix_alloc(size_t rows, size_t cols);

void matrix_free(Matrix* matrix);

Matrix* matrix_clone(const Matrix* m);

Matrix* matrix_resize(Matrix* m, size_t rows, size_t cols);

double matrix_get(const Matrix* matrix, size_t row, size_t col);

void matrix_set(Matrix* matrix, size_t row, size_t col, double value);

double *matrix_get_elem(const Matrix* matrix, size_t i, size_t j);

void matrix_print(const Matrix* matrix);

Matrix* zero_matrix_set(Matrix* matrix);

Matrix* zero_matrix_alloc(size_t rows, size_t cols);

Matrix* matrix_create_unit_square(size_t size);

Matrix* matrix_assign(Matrix* m1, const Matrix* m2);

#endif // STRUCT_H_INCLUDED

#include "gauss.h"

Matrix* inverse_matrix(const Matrix* m) {
    if (m->rows != m->cols) {
        return NULL;
    }
    Matrix* result = matrix_create_unit_square(m->rows);
    if (result == NULL) {
        return NULL;
    }
    Matrix* temp = matrix_clone(m);
    if (temp == NULL) {
        matrix_free(result);
        return NULL;
    }
    for (size_t i = 0; i < temp->rows; ++i) {
        size_t row = i;
        while (row < temp->rows && matrix_get(temp, row, i) == 0) {
            row++;
        }
        if (row == temp->rows) {
            matrix_free(result);
            matrix_free(temp);
            return NULL;
        }
        permute_string(temp, i, row);
        permute_string(result, i, row);

        double element = matrix_get(temp, i, i);
        multiply_row(temp, 1 / element, i);
        multiply_row(result, 1 / element, i);

        for (size_t j = 0; j < temp->rows; ++j) {
            if (j != i) {
                double scalar = -matrix_get(temp, j, i);

                for (size_t k = 0; k < temp->cols; ++k) {
                    matrix_set(temp, j, k, matrix_get(temp, j, k) + scalar * matrix_get(temp, i, k));
                    matrix_set(result, j, k, matrix_get(result, j, k) + scalar * matrix_get(result, i, k));
                }
            }
        }
    }
    matrix_free(temp);
    return result;
}

Matrix* solve_system(const Matrix* A, const Matrix* B, Matrix* x) {
    if (A->rows != A->cols) {
        return NULL;
    }
    Matrix *A_inv = inverse_matrix(A);
    if (A_inv == NULL) {
        return NULL;
    }
    x = matrix_multiply(A_inv, B);
    matrix_free(A_inv);
    return x;
}

#include "exp.h"

Matrix* matrix_power(const Matrix* A, int power, Matrix* res) {
    if (power == 0) {
        matrix_free(res);
        return matrix_create_unit_square(A->rows);
    }
    else if (power == 1) {
        matrix_free(res);
        return matrix_clone(A);
    }
    else {
        Matrix* temp = matrix_clone(A);
        for (int i = 2; i <= power; i++) {
            matrix_free(res);
            res = matrix_multiply(temp, A);
            matrix_assign(temp, res);
        }
        matrix_free(temp);
        return res;
    }
}

Matrix* matrix_exponential(const Matrix *A, double eps) {
    Matrix *result = matrix_create_unit_square(A->rows);
    Matrix *temp = matrix_clone(A);
    double n_factorial = 1;
    double norm_term = 0;
    for (int n = 1; ; n++) {
        matrix_power(A, n, temp);
        n_factorial *= n;
        matrix_multiply_scalar(temp, 1.0 / n_factorial);
        matrix_sum(result, result, temp);
        norm_term = max_row_norm(temp);
        if (norm_term < eps) {
            break;
        }
    }
    matrix_free(temp);
    return result;
}


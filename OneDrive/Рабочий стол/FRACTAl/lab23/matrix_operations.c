#include <stdlib.h>
#include "operations.h"
#include <math.h>

Matrix* matrix_add(Matrix* m1, const Matrix* m2) {
    if (m1->rows != m2->rows || m1->cols != m2->cols) {
        // Некорректные размеры матриц
        return NULL;
    }
    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m1->cols; j++) {
            double sum =  matrix_get(m1, i, j) + matrix_get(m2, i, j);
            matrix_set(m1, i, j, sum);
        }
    }
    return m1;
}

Matrix* matrix_sum(Matrix* m, const Matrix* m1, const Matrix* m2){
    if (m1->rows != m2->rows || m1->cols != m2->cols) {
        // Некорректные размеры матриц
        return NULL;
    }
    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m1->cols; j++) {
            double sum =  matrix_get(m1, i, j) + matrix_get(m2, i, j);
            matrix_set(m, i, j, sum);
        }
    }
    return m;
}

Matrix* matrix_multiply_scalar(Matrix* matrix, double scalar) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            double multi = matrix_get(matrix, i, j) * scalar;
            matrix_set(matrix, i, j, multi);
        }
    }
    return matrix;
}

Matrix* matrix_multiply(const Matrix* m1, const Matrix* m2) {
    if (m1->cols != m2->rows) {
        return NULL;
    }
    Matrix* result = matrix_alloc(m1->rows, m2->cols);
    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m2->cols; j++) {
            matrix_set(result, i, j, 0);
            double multi;
            for (int k = 0; k < m1->cols; k++) {
                multi +=  matrix_get(m1, i, k) * matrix_get(m2, k, j);
                matrix_set(result, i, j, multi);
            }
            multi = 0;
        }
    }
    return result;
}

Matrix* matrix_transpose_simple(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = i + 1; j < matrix->cols; j++) {
             double key1 = matrix_get(matrix, i, j);
             double key2 = matrix_get(matrix, j, i);
             matrix_set(matrix, i, j, key2);
             matrix_set(matrix, j, i, key1);
        }
    }
    return matrix;
}

Matrix* matrix_transpose(const Matrix* matrix, Matrix* result) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            double key = matrix_get(matrix, j, i);
            matrix_set(result, i, j, key);;
        }
    }
    return result;
}

Matrix* multiply_row(Matrix* matrix, double scalar,  size_t row) {
    for (size_t i = 0; i < matrix->cols; i++) {
        double key = matrix_get(matrix, row, i);
        matrix_set(matrix, row, i, key * scalar);
    }
    return matrix;
}


Matrix* add_strings(Matrix* matrix, size_t row1, size_t row2) {
    for (size_t i = 0; i < matrix->cols; i++) {
        double key = matrix_get(matrix, row1, i) + matrix_get(matrix, row2, i);
        matrix_set(matrix, row1, i, key);
    }
    return matrix;
}

Matrix* add_multiply_row_by_scalar(Matrix* m, size_t k, size_t t, double scalar){
    for (size_t i = 0; i < m->cols; ++i) {
        matrix_set(m, k, i, matrix_get(m, k, i) + scalar * matrix_get(m, t, i));
    }
    return m;
}

Matrix* permute_string(Matrix* matrix, size_t row1, size_t row2) {
    for (size_t i = 0; i < matrix->cols; i++) {
        double key1 = matrix_get(matrix, row1, i);
        double key2 = matrix_get(matrix, row2, i);
        matrix_set(matrix, row1, i, key2);
        matrix_set(matrix, row2, i, key1);
    }
    return matrix;
}

double max_row_norm(const Matrix* matrix) {
    double max = 0.0;
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            double abs_value = fabs(matrix_get(matrix, i, j));
            if (abs_value > max) {
                max = abs_value;
            }
        }
    }
    return max;
}

double max_col_norm(const Matrix* matrix) {
    double max = 0.0;
    for (int j = 0; j < matrix->cols; j++) {
        for (int i = 0; i < matrix->rows; i++) {
            double abs_value = fabs(matrix_get(matrix, i, j));
            if (abs_value > max) {
                max = abs_value;
            }
        }
    }
    return max;
}

Matrix* allocate_submatrix(const Matrix* matrix, size_t excluding_row, size_t excluding_col, Matrix* submatrix) {
    if (excluding_row >= matrix->rows || excluding_col >= matrix->cols) {
        return NULL;
    }
    size_t r = 0, c = 0;
    for (size_t i = 0; i < matrix->rows; ++i) {
        if (i == excluding_row) {
            continue;
        }
        for (size_t j = 0; j < matrix->cols; ++j) {
            if (j == excluding_col) {
                continue;
            }
            matrix_set(submatrix, r, c, matrix_get(matrix, i, j));
            c++;
        }
        r++;
        c = 0;
    }
    return submatrix;
}

double matrix_determinant(const Matrix* m) {
    if (m->rows != m->cols) {
        return 0;
    }
    if (m->rows == 1) {
        return matrix_get(m, 0, 0);
    }
    double det = 0;
    Matrix* sub = matrix_alloc(m->rows - 1, m->cols - 1);
    if (!sub) {
        return 0;
    }
    for (size_t j = 0; j < m->cols; ++j) {
        allocate_submatrix(m, 0, j, sub);
        det += pow(-1, j + 1) * matrix_get(m, 0, j) * matrix_determinant(sub);
    }

    matrix_free(sub);
    return det;
}

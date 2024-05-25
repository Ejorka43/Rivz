#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <locale.h>
#include <math.h>
#include "struct.h"
#include "operations.h"
#include "gauss.h"
#include "exp.h"

int main(){
    setlocale(LC_CTYPE, "Russian");
    while(1){
        printf("Выберите, что выполнить: \n");
        printf("1) Структура матрицы \n");
        printf("2) Операции с матрицами \n");
        printf("3) Метод Гаусса \n");
        printf("4) Матричная экспонента \n");

        int choice;
        scanf("%d", &choice);
        switch(choice){
        case 1:
            //Создание матрицы
            printf("Введите размер матрицы (первое — высота, второе — ширина):\n");
            size_t h1, w1;
            scanf("%zu %zu", &h1, &w1);
            Matrix* matrix = matrix_alloc(h1, w1);
            if (matrix == NULL) {
                return 1;
            }
            if (matrix != NULL) {
                printf("Матрица успешно создана.\n");
            }
            printf("Введите элементы матрицы:\n");
            for (size_t i = 0; i < h1; i++) {
                for (size_t j = 0; j < w1; j++) {
                    double element;
                    scanf("%lf", &element);
                    matrix_set(matrix, i, j, element);
                }
            }
            printf("Матрица:\n");
            matrix_print(matrix);

            printf("Введите индексы элемента матрицы к которым хотите получить доступ:\n");
            size_t row, col;
            scanf("%zu %zu", &row, &col);
            printf("Элемент с i=%zu, j=%zu: %lf\n", row, col, *matrix_get_elem(matrix, row, col));

            //Клонирование матрицы
            Matrix* matrix2 = matrix_clone(matrix);
            printf("Клон матрицы:\n");
            matrix_print(matrix2);
            matrix_free(matrix);

            //Изменённая матрица
            printf("Введите измененный размер матрицы (сначала высота, затем ширина):\n");
            size_t h2, w2;
            scanf("%zu %zu", &h2, &w2);
            Matrix* matrix3 = matrix_resize(matrix2, h2, w2);
            printf("Изменённая матрица:\n");
            matrix_print(matrix3);
            matrix_free(matrix3);

            //Нулевая матрица
            printf("Введите размер нулевой матрицы (сначала высота, затем ширина):\n");
            size_t h3, w3;
            scanf("%zu %zu", &h3, &w3);
            Matrix* matrix4 = zero_matrix_alloc(h3, w3);
            printf("Zero matrix:\n");
            matrix_print(matrix4);
            matrix_free(matrix4);

            //Единичная матрица
            printf("Введите размер единичной квадратной матрицы: \n");
            size_t size;
            scanf("%zu", &size);
            Matrix* matrix5 = matrix_create_unit_square(size);
            printf("Единичная матрица:\n");
            matrix_print(matrix5);
            matrix_free(matrix5);

            break;

        case 2:
            printf("Введите размер первой матрицы (сначала высота, затем ширина):\n");
            size_t h4, w4;
            scanf("%zu %zu", &h4, &w4);
            Matrix* matrix6 = matrix_alloc(h4, w4);
            if (matrix6 == NULL) {
                return 1;
            }

            if (matrix6 != NULL) {
                printf("Матрица успешно создана.\n");
            }
            printf("Введите элементы матрицы:\n");
            for (size_t i = 0; i < h4; i++) {
                for (size_t j = 0; j < w4; j++) {
                    double element;
                    scanf("%lf", &element);
                    matrix_set(matrix6, i, j, element);
                }
            }

            printf("Введите размер второй матрицы (сначала высота, затем ширина):\n");
            size_t h5, w5;
            scanf("%zu %zu", &h5, &w5);
            Matrix* matrix7 = matrix_alloc(h5, w5);
            if (matrix7 == NULL) {
                return 1;
            }
            if (matrix7 != NULL) {
                printf("Матрица успешно создана.\n");
            }
            printf("Введите элементы матрицы:\n");
            for (size_t i = 0; i < h5; i++) {
                for (size_t j = 0; j < w5; j++) {
                    double element;
                    scanf("%lf", &element);
                    matrix_set(matrix7, i, j, element);
                }
            }

            //Сумма матриц
            Matrix* matrix72 = matrix_alloc(h5, w5);
            Matrix* result1 = matrix_sum(matrix72, matrix6, matrix7);
            printf("Сумма матриц:\n");
            matrix_print(matrix6);
            printf("+ \n");
            matrix_print(matrix7);
            printf("= \n");
            matrix_print(result1);
            matrix_free(result1);

            //Умножение матрицы на скаляр
            Matrix* matrix65 = matrix_clone(matrix6);
            printf("Введите скаляр на который будет умножена первая матрица: \n");
            double scalar;
            scanf("%lf", &scalar);
            matrix_multiply_scalar(matrix65, scalar);
            printf("Первая матрица умноженная на скаляр:\n");
            matrix_print(matrix65);
            matrix_free(matrix65);

            //Умножение матриц
            Matrix* result2 = matrix_multiply(matrix6, matrix7);
            printf("Перемноженные первая и вторая матрицы:\n");
            matrix_print(result2);
            matrix_free(result2);

            //Транспонирование матрицы
            Matrix* matrix66 = matrix_clone(matrix6);
            printf("Транспонирование первой матрицы двумя способами:\n");
            Matrix* result3 = matrix_alloc(h4, w4);
            matrix_transpose(matrix66, result3);
            matrix_transpose_simple(matrix66);
            matrix_print(result3);
            printf("\n");
            matrix_print(matrix66);

            matrix_free(result3);
            matrix_free(matrix66);
            matrix_free(matrix6);

            Matrix* matrix85 = matrix_clone(matrix7);
            Matrix* matrix86 = matrix_clone(matrix7);
            Matrix* matrix87 = matrix_clone(matrix7);
            Matrix* matrix88 = matrix_clone(matrix7);

            //Умножение строки на скаляр
            printf("Введите скаляр и номер строки второй матрицы (строка матрицы будет умножена на этот скаляр): \n");
            double scalar_row;
            size_t st0;
            scanf("%lf", &scalar_row);
            scanf("%zu", &st0);
            multiply_row(matrix85, scalar_row, st0);
            matrix_print(matrix85);
            matrix_free(matrix85);

            //Сумма двух строк
            printf("Выберите номера строк второй матрицы, которые будут суммироваться (к первой прибавится вторая): \n");
            size_t st1, st2;
            scanf("%zu", &st1);
            scanf("%zu", &st2);
            add_strings(matrix86, st1, st2);
            matrix_print(matrix86);
            matrix_free(matrix86);

            //Перестановка строк
            printf("Выберите номера строк второй матрицы, которые будут переставлены: \n");
            size_t st3, st4;
            scanf("%zu", &st3);
            scanf("%zu", &st4);
            permute_string(matrix87, st3, st4);
            matrix_print(matrix87);
            matrix_free(matrix87);

            //Матричная норма
            printf("Матричная норма по строкам: \n");
            printf("%lf \n", max_row_norm(matrix88));

            printf("Матричная норма по столбцам: \n");
            printf("%lf \n", max_col_norm(matrix88));
            matrix_free(matrix88);

            //Выделение подматрицы
            printf("Выберите номера строки и столбца для исключения из матрицы: \n");
            size_t st5, st6;
            scanf("%zu", &st5);
            scanf("%zu", &st6);
            Matrix* submatrix = matrix_alloc(h5 - 1, w5 - 1);
            allocate_submatrix(matrix7, st5, st6, submatrix);
            matrix_print(submatrix);
            matrix_free(submatrix);

            //Определитель матрицы
            printf("Определитель матрицы: \n");
            double det = matrix_determinant(matrix7);
            printf("%lf \n", det);
            matrix_free(matrix7);

            break;

        case 3:

            printf("Введите размер квадратной матрицы:\n");
            size_t h6;
            scanf("%zu", &h6);
            Matrix* matrixA = matrix_alloc(h6, h6);
            if (matrixA == NULL) {
                return 1;
            }
            if (matrixA != NULL) {
                printf("Матрица успешно создана.\n");
            }
            printf("Введите элементы матрицы A:\n");
            for (size_t i = 0; i < h6; i++) {
                for (size_t j = 0; j < h6; j++) {
                    double element;
                    scanf("%lf", &element);
                    matrix_set(matrixA, i, j, element);
                }
            }
            matrix_print(matrixA);

            Matrix* matrixB = matrix_alloc(h6, 1);
            if (matrixB == NULL) {
                return 1;
            }
            if (matrixB != NULL) {
                printf("Матрица успешно создана.\n");
            }
            printf("Введите элементы матрицы B:\n");
            for (size_t i = 0; i < h6; i++) {
                for (size_t j = 0; j < 1; j++) {
                    double element;
                    scanf("%lf", &element);
                    matrix_set(matrixB, i, j, element);
                }
            }
            matrix_print(matrixB);

            Matrix* matrixx = matrix_alloc(h6, 1);;
            Matrix* gauss_matrix = solve_system(matrixA, matrixB, matrixx);
            if (gauss_matrix != NULL) {
                printf("Матрица решений (x):\n");
                matrix_print(gauss_matrix);
                matrix_free(gauss_matrix);
            }
            else {
                printf("нет единственного решения.\n");
            }
            break;

        case 4:
            printf("Введите размер матрицы для операции exp:\n");
            size_t h10, w10;
            scanf("%zu %zu", &h10, &w10);
            Matrix* matrix10 = matrix_alloc(h10, w10);
            if (matrix10 == NULL) {
                return 1;
            }

            if (matrix10 != NULL) {
                printf("Матрица успешно создана.\n");
            }

            printf("Введите элементы матрицы:\n");
            for (size_t i = 0; i < h10; i++) {
                for (size_t j = 0; j < w10; j++) {
                    double element;
                    scanf("%lf", &element);
                    matrix_set(matrix10, i, j, element);
                }
            }
            Matrix* matrix11 = matrix_exponential(matrix10, 0.00000001);
            matrix_print(matrix11);
            matrix_free(matrix11);

            break;

        default:
            printf("Ошибка ввода \n");
            return 0;
        }
    }
    return 0;
}

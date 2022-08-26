#include "s21_matrix.h"

// void s21_pr(matrix_t A) {
//     for (int i = 0; i < A.rows; i++) {
//         for (int j = 0; j < A.columns; j++) {
//             printf("%35.30lf ", A.matrix[i][j]);
//         }
//         printf("\n");
//     }
//     printf("\n");
// }

// void completion_matrix(matrix_t *result) {
//     for (int i = 0; i < result->rows; i++) {
//         for (int j = 0; j < result->columns; j++) {
//             scanf("%lf", &result->matrix[i][j]);
//         }
//     }
// }

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int bug = 0;
    if (rows < 1 || columns < 1) {
        bug = 1;
    } else {
        result->rows = rows;
        result->columns = columns;
        result->matrix = (double**)calloc(rows, sizeof(double*));
        for (int i = 0; i < rows; i++)
            result->matrix[i] = (double*)calloc(columns, sizeof(double));
    }
    return bug;
}

void s21_remove_matrix(matrix_t *A) {
    if (A->matrix) {
        for (int i = 0; i < A->rows; i++) {
                free(A->matrix[i]);
        }
        free(A->matrix);
        A->matrix = NULL;
    }
    A->rows = 0;
    A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int result = SUCCESS;
    if (A == NULL || A->rows < 1 || A->columns < 1 || B == NULL || B->rows < 1 || B->columns < 1) {
        result = FAILURE;
    } else if (A->columns != B->columns || A->rows != B->rows) {
        result = FAILURE;
    } else {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {           // this is A != B
                    result = FAILURE;
                }
            }
        }
    }
    return result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int bug = 0;
    // A & B  are same
    if (A == NULL || A->rows < 1 || A->columns < 1 || B == NULL || B->rows < 1 || B->columns < 1) {
        bug = 1;
    } else if (A->rows != B->rows || A->columns != B->columns) {
        bug = 2;
    } else {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
            }
        }
    }
    return bug;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int bug = 0;
    // A & B  are same
    if (A == NULL || A->rows < 1 || A->columns < 1 || B == NULL || B->rows < 1 || B->columns < 1) {
        bug = 1;
    } else if (A->rows != B->rows || A->columns != B->columns) {
        bug = 2;
    } else {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
            }
        }
    }
    return bug;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int bug = 0;
    if (A == NULL || A->rows < 1 || A->columns < 1) {
        bug = 1;
    } else {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] * number;
            }
        }
    }
    return bug;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int bug = 0;
    // A->rows & B->columns are same
    if (A == NULL || A->rows < 1 || A->columns < 1 || B == NULL || B->rows < 1 || B->columns < 1) {
        bug = 1;
    } else if (A->columns != B->rows) {
        bug = 2;
    } else {
        s21_create_matrix(A->rows, B->columns, result);
        for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
                for (int k = 0; k < A->columns; k++)
                    result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
        }
    }
    return bug;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    int bug = 0;
    if (A == NULL || A->rows < 1 || A->columns < 1) {
        bug = 1;
    } else {
        s21_create_matrix(A->columns, A->rows, result);
        for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
                result->matrix[i][j] = A->matrix[j][i];
            }
        }
    }
    return bug;
}

void s21_mini_matrix(int n, int c, matrix_t *A, matrix_t *minimat) {
    s21_create_matrix(A->rows - 1, A->columns - 1, minimat);
    int i_m = 0;
    for (int i = 0; i < A->rows; i++) {
        int j_m = 0;
        if (i == n) continue;
        for (int j = 0; j < A->columns; j++) {
            if (j != c) {
                minimat->matrix[i_m][j_m] = A->matrix[i][j];
            j_m++;
            }
        }
        i_m++;
    }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int bug = 0;
    if (A == NULL || A->rows < 1 || A->columns < 1) {
        bug = 1;
    } else {
        s21_create_matrix(A->columns, A->rows, result);
        for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
                matrix_t minor_mat;
                s21_mini_matrix(i, j, A, &minor_mat);
                double r;
                s21_determinant(&minor_mat, &r);
                result->matrix[i][j] = pow((-1), i + j) * r;
                s21_remove_matrix(&minor_mat);
            }
        }
    }
    return bug;
}


double s21_det(int n, matrix_t *A) {
    matrix_t submat;
    s21_create_matrix(A->rows, A->columns, &submat);
    double r = 0;
    if (n == 2) {
        r = A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
    } else {
        for (int c = 0; c < n; c++) {
            int subi = 0;                                             // maybe change s21_mini_matrix?
            for (int i = 1; i < n; i++) {
                int subj = 0;
                for (int j = 0; j < n; j++) {
                    if (j != c) {
                        submat.matrix[subi][subj] = A->matrix[i][j];
                    subj++;
                    }
                }
                subi++;
            }
            r += (pow(-1, c) * A->matrix[0][c] * s21_det(n - 1, &submat));
        }
    }
    s21_remove_matrix(&submat);
    return r;
}

int s21_determinant(matrix_t *A, double *result) {
    int bug = 0;
    // A->rows & A->columns are same
    if (A == NULL || A->rows < 1 || A->columns < 1) {
        bug = 1;
    } else if (A->columns != A->rows) {
        bug = 2;
    } else {
        if (A->rows == 1)
            *result = A->matrix[0][0];
        else
            *result = s21_det(A->rows, A);
    }
    return bug;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int bug = 0;
    double r;
    // A->rows & A->columns are same
    if (A == NULL || A->rows < 1 || A->columns < 1) {
        bug = 1;
    } else if (A->columns != A->rows) {
        bug = 2;
    } else if (!s21_determinant(A, &r) && !r) {
        bug = 2;
    } else {
        matrix_t complements, transpose;
        s21_calc_complements(A, &complements);
        s21_transpose(&complements, &transpose);
        s21_create_matrix(A->columns, A->rows, result);
        for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
                result->matrix[i][j] = 1/r * transpose.matrix[i][j];
            }
        }
        s21_remove_matrix(&complements);
        s21_remove_matrix(&transpose);
    }
    return bug;
}

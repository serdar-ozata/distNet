//
// Created by serdar on 10/23/24.
//

#include "Matrix.h"
#include <stdlib.h>
#include <cstring>
#include <cmath>

Matrix *create_matrix(int m, int n) {
    Matrix *mat = (Matrix *) malloc(sizeof(Matrix));
    mat->m = m;
    mat->n = n;
    mat->data = (double **) malloc(m * sizeof(double *));
    for (int i = 0; i < m; i++) {
        mat->data[i] = (double *) malloc(n * sizeof(double));
    }
    return mat;
}

void free_matrix(Matrix *mat) {
    for (int i = 0; i < mat->m; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}

void GEMM(Matrix *A, Matrix *B, Matrix *C) {
    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j < B->n; j++) {
            C->data[i][j] = 0;
            for (int k = 0; k < A->n; k++) {
                C->data[i][j] += A->data[i][k] * B->data[k][j];
            }
        }
    }
}

void GEMM_NT(Matrix *A, Matrix *B, Matrix *C) {
    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j < B->m; j++) {
            C->data[i][j] = 0;
            for (int k = 0; k < A->n; k++) {
                C->data[i][j] += A->data[i][k] * B->data[j][k];
            }
        }
    }
}

void GEMM_TN(Matrix *A, Matrix *B, Matrix *C) {
    memset(C->data[0], 0, C->m * C->n * sizeof(double));
    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j < A->n; j++) {
            for (int k = 0; k < B->n; k++) {
                C->data[j][k] += A->data[i][j] * B->data[i][k];
            }
        }
    }
}

void matrix_fill(Matrix *mat, double value) {
    for (int i = 0; i < mat->m; i++) {
        memset(mat->data[i], value, mat->n * sizeof(double));
    }
}

void matrix_random(Matrix *mat, unsigned int seed) {
    srand(seed);
    double min = -sqrt(6.0 / (mat->m + mat->n));
    double max = sqrt(6.0 / (mat->m + mat->n));
    for (int i = 0; i < mat->m; i++) {
        for (int j = 0; j < mat->n; j++) {
            mat->data[i][j] = min + (max - min) * ((double) rand() / RAND_MAX);
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (int i = 0; i < matrix.m; i++) {
        for (int j = 0; j < matrix.n; j++) {
            os << matrix.data[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

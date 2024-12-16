//
// Created by serdar on 10/23/24.
//

#include "Matrix.h"
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>

Matrix *create_matrix(int m, int n) {
    Matrix *mat = (Matrix *) malloc(sizeof(Matrix));
    mat->m = m;
    mat->n = n;
    mat->data = (double *) malloc (m * n * sizeof(double));
    return mat;
}

void free_matrix(Matrix *mat) {
    free(mat->data);
    mat->data = nullptr;
    free(mat);
}

void GEMM(Matrix *A, Matrix *B, Matrix *C) {
    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j < B->n; j++) {
            C->data[C->n * i + j] = 0;
            for (int k = 0; k < A->n; k++) {
                C->data[C->n * i + j] += A->data[A->n * i + k] * B->data[B->n * k + j];
            }
        }
    }
}

void GEMM_NT(Matrix *A, Matrix *B, Matrix *C) {
    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j < B->m; j++) {
            C->data[C->n * i + j] = 0;
            for (int k = 0; k < A->n; k++) {
                C->data[C->n * i + j] += A->data[A->n * i + k] * B->data[B->n * j + k];
            }
        }
    }
}

void GEMM_TN(Matrix *A, Matrix *B, Matrix *C) {
    memset(C->data, 0, C->m * C->n * sizeof(double));
    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j < A->n; j++) {
            for (int k = 0; k < B->n; k++) {
                C->data[C->n * j + k] += A->data[A->n * i + j] * B->data[B->n * i + k];
            }
        }
    }
}

void matrix_fill(Matrix *mat, double value) {
    std::fill_n(mat->data, mat->m * mat->n, value);
}

void matrix_random(Matrix *mat, unsigned int seed) {
    srand(seed);
    double min = -sqrt(6.0 / (mat->m + mat->n));
    double max = sqrt(6.0 / (mat->m + mat->n));
    for (int i = 0; i < mat->m * mat->n; i++) {
        mat->data[i] = min + (max - min) * (double) rand() / RAND_MAX;
    }
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (int i = 0; i < matrix.m; i++) {
        for (int j = 0; j < matrix.n; j++) {
            os << matrix.data[matrix.n * i + j] << " ";
        }
        os << std::endl;
    }
    return os;
}

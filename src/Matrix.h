//
// Created by serdar on 10/23/24.
//

#ifndef DISTNET_MATRIX_H
#define DISTNET_MATRIX_H
#include <iostream>

typedef struct {
    int m;
    int n;
    double **data;
} Matrix;

Matrix *create_matrix(int m, int n);

void free_matrix(Matrix *mat);

void GEMM(Matrix *A, Matrix *B, Matrix *C);

void GEMM_NT(Matrix *A, Matrix *B, Matrix *C);

void GEMM_TN(Matrix *A, Matrix *B, Matrix *C);

void matrix_fill(Matrix *mat, double value);

void matrix_random(Matrix *mat, unsigned int seed);

// operator << for matrix datatype
std::ostream &operator<<(std::ostream &os, const Matrix &matrix);


#endif //DISTNET_MATRIX_H

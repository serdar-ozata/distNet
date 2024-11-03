//
// Created by serdar on 10/23/24.
//

#ifndef DISTNET_CONVOLUTIONAL_H
#define DISTNET_CONVOLUTIONAL_H


#include <cstdio>
#include "Layer.h"
#include "mpi.h"

typedef enum {
    ZERO,
    NONE,
    SAME,
} PaddingType;


class Convolutional : public Layer {
private:
    int stride;
    PaddingType padding_type;
    Matrix *kernel;
    Matrix *bias;
    Matrix *m_kernel;
    Matrix *m_bias;
    Matrix *v_kernel;
    Matrix *v_bias;
    Matrix *kernel_grad;
    Matrix *bias_grad;
    double beta1 = 0.9;
    double beta2 = 0.999;
    double epsilon = 1e-8;
    double lr = 0.001;
public:
    Convolutional(Matrix *input, int kernel_size, int stride, PaddingType padding_type, unsigned int seed) : Layer(input) {
        this->stride = stride;
        this->padding_type = padding_type;
        if (kernel_size % 2 == 0 || kernel_size < 1) {
            fprintf(stderr, "Invalid kernel size\n");
        }
        if (stride < 1) {
            fprintf(stderr, "Invalid stride\n");
        }
        int output_size;
        if (padding_type == NONE) {
            output_size = (input->m - kernel_size + 1) / stride;
        } else {
            output_size = input->m / stride;
        }
    }

};


#endif //DISTNET_CONVOLUTIONAL_H

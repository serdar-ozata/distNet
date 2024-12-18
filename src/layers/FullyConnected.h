//
// Created by serdar on 10/23/24.
//

#ifndef DISTNET_FULLYCONNECTED_H
#define DISTNET_FULLYCONNECTED_H


#include "Layer.h"
#include "cmath"
#include "mpi.h"
#include <cstring>
class FullyConnected : public Layer {
    Matrix *weights;
    Matrix *bias;
    Matrix *m_weights;
    Matrix *m_bias;
    Matrix *v_weights;
    Matrix *v_bias;
    Matrix *weights_grad;
    Matrix *bias_grad;
    double beta1 = 0.9;
    double beta2 = 0.999;
    double epsilon = 1e-8;
    double lr = 0.001;
public:
    FullyConnected(Matrix *input, int output_size) : Layer(input) {
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        output = create_matrix(input->m, output_size);
        weights = create_matrix(input->n, output_size);
        bias = create_matrix(1, output_size);
        m_weights = create_matrix(input->n, output_size);
        m_bias = create_matrix(1, output_size);
        v_weights = create_matrix(input->n, output_size);
        v_bias = create_matrix(1, output_size);
        weights_grad = create_matrix(input->n, output_size);
        bias_grad = create_matrix(1, output_size);
        if (world_rank == 0) {
            matrix_random(weights, 123); // just a random seed
        } else {
            matrix_fill(weights, 0);
        }
        MPI_Bcast(weights->data, weights->m * weights->n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        matrix_fill(bias, 0);
        matrix_fill(m_weights, 0);
        matrix_fill(m_bias, 0);
        matrix_fill(v_weights, 0);
        matrix_fill(v_bias, 0);
    }

    void forward() override {
        GEMM(input, weights, output);
        for (int i = 0; i < output->m; i++) {
            for (int j = 0; j < output->n; j++) {
                output->data[output->n * i + j] += bias->data[j];
            }
        }
    }
    void calc_bias_grad(Matrix* error) {
        memset(bias_grad->data, 0, bias_grad->m * bias_grad->n * sizeof(double));
        for (int i = 0; i < error->m; i++) {
            for (int j = 0; j < error->n; j++) {
                bias_grad->data[j] += error->data[error->n * i + j];
            }
        }
    }

    Matrix *backward(Matrix *error, int step) override {
        // grads
        Matrix * new_error = create_matrix(error->m, weights->m);
        GEMM_NT(error, weights, new_error);
        GEMM_TN(input, error, weights_grad);
        calc_bias_grad(error);

        // sum grads
        MPI_Allreduce(MPI_IN_PLACE, weights_grad->data, weights_grad->m * weights_grad->n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        MPI_Allreduce(MPI_IN_PLACE, bias_grad->data, bias_grad->m * bias_grad->n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        // backprop
        back_prop(weights, weights_grad, m_weights, v_weights, step);
        back_prop(bias, bias_grad, m_bias, v_bias, step);
        // replace error
        free_matrix(error);
        return new_error;
    }

    void back_prop(Matrix* weights, Matrix *grad, Matrix *m, Matrix *v, int step) {
        for (int i = 0; i < grad->m; i++) {
            for (int j = 0; j < grad->n; j++) {
                m->data[grad->n * i + j] = beta1 * m->data[grad->n * i + j] + (1 - beta1) * grad->data[grad->n * i + j];
                v->data[grad->n * i + j] = beta2 * v->data[grad->n * i + j] + (1 - beta2) * grad->data[grad->n * i + j] * grad->data[grad->n * i + j];
                double m_hat = m->data[grad->n * i + j] / (1 - pow(beta1, step));
                double v_hat = v->data[grad->n * i + j] / (1 - pow(beta2, step));
                weights->data[grad->n * i + j] -= lr * m_hat / (sqrt(v_hat) + epsilon);
            }
        }
    }
    ~FullyConnected() {
        free_matrix(weights);
        free_matrix(bias);
        free_matrix(m_weights);
        free_matrix(m_bias);
        free_matrix(v_weights);
        free_matrix(v_bias);
        free_matrix(weights_grad);
        free_matrix(bias_grad);
    }
    void changeDataSize(int new_m){
        free_matrix(output);
        output = create_matrix(new_m, output->n);
    }
};

#endif //DISTNET_FULLYCONNECTED_H

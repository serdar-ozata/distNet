//
// Created by serdar on 10/23/24.
//

#ifndef DISTNET_SOFTMAXCENTROPYCLASSIFICATION_H
#define DISTNET_SOFTMAXCENTROPYCLASSIFICATION_H


#include "Loss.h"

class SoftmaxCEntropyClassification: public Loss {
public:
    SoftmaxCEntropyClassification(Matrix *labels) : Loss(labels) {}
    // todo: upgrade so that it can output more information
    void eval(Matrix *out) override {
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        checkDims(out);
        Matrix * softmax = create_matrix(out->m, out->n);
        for (int i = 0; i < out->m; i++) {
            double sum = 0;
            for (int j = 0; j < out->n; j++) {
                softmax->data[out->n * i + j] = exp(out->data[out->n * i + j]);
                sum += softmax->data[out->n * i + j];
            }
            for (int j = 0; j < out->n; j++) {
                softmax->data[out->n * i + j] /= sum;
            }
        }
        double tp = 0, global_tp = 0;
        unsigned int total = 0, global_total = 0;
        for (int i = 0; i < out->m; i++) {
            int maxIndex = 0;
            for (int j = 0; j < out->n; j++) {
                if (softmax->data[out->n * i + j] > softmax->data[out->n * i + maxIndex]) {
                    maxIndex = j;
                }
            }
            int maxIndexLabel = 0;
            for (int j = 0; j < out->n; j++) {
                if (labels->data[out->n * i + j] > labels->data[out->n * i + maxIndexLabel]) {
                    maxIndexLabel = j;
                }
            }
            if (maxIndex == maxIndexLabel) {
                tp++;
            }
            total++;
        }
        MPI_Reduce(&tp, &global_tp, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce(&total, &global_total, 1, MPI_UNSIGNED, MPI_SUM, 0, MPI_COMM_WORLD);
        if (world_rank == 0) {
            printf("Accuracy: %f\n", global_tp / global_total);
        }
    }

    Matrix *get_error_prime(Matrix *out) override {
        checkDims(out);
        Matrix* error = create_matrix(out->m, out->n); // used for both softmax and cross entropy
        for (int i = 0; i < out->m; i++) {
            double sum = 0;
            for (int j = 0; j < out->n; j++) {
                error->data[out->n * i + j] = exp(out->data[out->n * i + j]);
                sum += error->data[out->n * i + j];
            }
            for (int j = 0; j < out->n; j++) {
                error->data[out->n * i + j] /= sum;
            }
        }

        for (int i = 0; i < out->m * out->n; i++) {
            error->data[i] = error->data[i] - labels->data[i];
        }

        return error;
    }
};


#endif //DISTNET_SOFTMAXCENTROPYCLASSIFICATION_H

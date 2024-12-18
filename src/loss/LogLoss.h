//
// Created by serdar on 12/18/24.
//

#ifndef DISTNET_LOGLOSS_H
#define DISTNET_LOGLOSS_H

#include "Loss.h"

// for binary classification
class LogLoss : public Loss {
public:
    LogLoss(Matrix *labels) : Loss(labels) {}

    double sigmoid(double x) {
        return 1 / (1 + exp(-x));
    }
    double epsilon = 1e-10; // small value to prevent log(0)
    void eval(Matrix *out) override {
        checkDims(out);
        if (out->n != 1) {
            printf("Error: LogLoss is only for binary classification\n");
            exit(1);
        }
        // apply sigmoid
        for (int i = 0; i < out->m; i++) {
            out->data[i] = sigmoid(out->data[i]);
        }
        double loss = 0;
        for (int i = 0; i < out->m; i++) {
            loss += labels->data[i] * log(out->data[i] + epsilon) + (1 - labels->data[i]) * log(1 - out->data[i] + epsilon);
        }
        double total_loss = 0;
        MPI_Reduce(&loss, &total_loss, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        if (world_rank == 0) {
//            printf("Loss: %f\n", -total_loss);
        }
        // accuracy
        int correct = 0;
        for (int i = 0; i < out->m; i++) {
            if (out->data[i] > 0.5 && labels->data[i] == 1) {
                correct++;
            } else if (out->data[i] <= 0.5 && labels->data[i] == 0) {
                correct++;
            }
        }
        int total_correct = 0;
        MPI_Reduce(&correct, &total_correct, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);
        if (world_rank == 0) {
//            printf("Accuracy: %f\n", (double) total_correct / (world_size * out->m));
        }
    }
    // we have to take the derivative of both sigmoid and log loss
    // dy_h/dx = sigmoid(x) * (1 - sigmoid(x))
    // L = y(ln(sigmoid(x)) + (1 - y)ln(1 - sigmoid(x)))
    // dL/dx = y - sigmoid(x)
    Matrix *get_error_prime(Matrix *out) override {
        checkDims(out);
        if (out->n != 1) {
            printf("Error: LogLoss is only for binary classification\n");
            exit(1);
        }
        Matrix *error = create_matrix(out->m, out->n);
        for (int i = 0; i < out->m; i++) {
            error->data[i] = -labels->data[i] + out->data[i];
        }
        return error;
    }
};
#endif //DISTNET_LOGLOSS_H

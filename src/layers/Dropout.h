//
// Created by serdar on 10/23/24.
//

#ifndef DISTNET_DROPOUT_H
#define DISTNET_DROPOUT_H


#include <cstdlib>
#include "ActivationLayer.h"

class Dropout : public ActivationLayer {
    float dropout_rate = 0.3;
    bool* mask;
public:
    Dropout(Matrix *input) : ActivationLayer(input) {
        mask = new bool[input->m * input->n];
    }

    Dropout(Matrix *input, float dropout_rate) : ActivationLayer(input) {
        this->dropout_rate = dropout_rate;
        mask = new bool[input->m * input->n];
    }

    void forward() override {
        for (int i = 0; i < input->m; i++) {
            for (int j = 0; j < input->n; j++) {
                mask[i * input->n + j] = ((double) rand() / RAND_MAX) > dropout_rate;
                output->data[i][j] = mask[i * input->n + j] * input->data[i][j];
            }
        }
    }

    Matrix * backward(Matrix *error, int step) override {
        for (int i = 0; i < input->m; i++) {
            for (int j = 0; j < input->n; j++) {
                error->data[i][j] = mask[i * input->n + j] * error->data[i][j];
            }
        }
        return error;
    }
    ~Dropout() {
        delete[] mask;
    }
};


#endif //DISTNET_DROPOUT_H

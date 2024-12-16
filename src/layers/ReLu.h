//
// Created by serdar on 10/23/24.
//

#ifndef DISTNET_RELU_H
#define DISTNET_RELU_H
#include "ActivationLayer.h"
#include <cmath>

class ReLu : public ActivationLayer {
public:
    ReLu(Matrix *input) : ActivationLayer(input) {
    }

    void forward() override {
        for (int i = 0; i < input->m * input->n; i++) {
            output->data[i] = fmax(0, input->data[i]);
        }
    }

    Matrix * backward(Matrix *error, int step) override {
        for (int i = 0; i < input->m * input->n; i++) {
            error->data[i] *= input->data[i] > 0 ? 1 : 0;
        }
        return error;
    }
};
#endif //DISTNET_RELU_H

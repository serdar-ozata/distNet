//
// Created by serdar on 10/23/24.
//

#ifndef DISTNET_LRELU_H
#define DISTNET_LRELU_H

#include <cmath>
#include "ActivationLayer.h"

class LReLu : public ActivationLayer {
    float alpha = 0.01;
public:
    LReLu(Matrix *input) : ActivationLayer(input) {
    }

    LReLu(Matrix *input, float alpha) : ActivationLayer(input) {
        this->alpha = alpha;
    }

    void forward() override {
        for (int i = 0; i < input->m * input->n; i++) {
            output->data[i] = fmax(alpha * input->data[i], input->data[i]);
        }
    }

    Matrix * backward(Matrix *error, int step) override {
        for (int i = 0; i < input->m * input->n; i++) {
            error->data[i] *= input->data[i] > 0 ? 1 : alpha;
        }
        return error;
    }
};


#endif //DISTNET_LRELU_H

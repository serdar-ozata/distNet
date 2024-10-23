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
        for (int i = 0; i < input->m; i++) {
            for (int j = 0; j < input->n; j++) {
                output->data[i][j] = fmax(alpha * input->data[i][j], input->data[i][j]);
            }
        }
    }

    Matrix * backward(Matrix *error, int step) override {
        for (int i = 0; i < input->m; i++) {
            for (int j = 0; j < input->n; j++) {
                input->data[i][j] = (input->data[i][j] > 0) ? error->data[i][j] : alpha * error->data[i][j];
            }
        }
        return error;
    }
};


#endif //DISTNET_LRELU_H

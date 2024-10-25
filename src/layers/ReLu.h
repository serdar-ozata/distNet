//
// Created by serdar on 10/23/24.
//

#ifndef DISTNET_RELU_H
#define DISTNET_RELU_H
#include "ActivationLayer.h"
#include <math.h>

class ReLu : public ActivationLayer {
public:
    ReLu(Matrix *input) : ActivationLayer(input) {
    }

    void forward() override {
        for (int i = 0; i < input->m; i++) {
            for (int j = 0; j < input->n; j++) {
                output->data[i][j] = fmax(0, input->data[i][j]);
            }
        }
    }

    Matrix * backward(Matrix *error, int step) override {
        for (int i = 0; i < input->m; i++) {
            for (int j = 0; j < input->n; j++) {
                error->data[i][j] *= input->data[i][j] > 0 ? 1 : 0;
            }
        }
        return error;
    }
};
#endif //DISTNET_RELU_H

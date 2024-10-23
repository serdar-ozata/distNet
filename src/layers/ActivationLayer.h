//
// Created by serdar on 10/23/24.
//

#ifndef DISTNET_ACTIVATIONLAYER_H
#define DISTNET_ACTIVATIONLAYER_H


#include "Layer.h"

class ActivationLayer : public Layer {
private:
    void alloc_output() {
        output = create_matrix(input->m, input->n);
    }
public:
    ActivationLayer(Matrix *input) : Layer(input) {
        alloc_output();
    }
};

#endif //DISTNET_ACTIVATIONLAYER_H

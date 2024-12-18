//
// Created by serdar on 10/23/24.
//

#ifndef DISTNET_LAYER_H
#define DISTNET_LAYER_H

#include "../Matrix.h"

class Layer {
protected:

public:
    Matrix *input, *output;
    Layer(Matrix *input) {
        this->input = input;
    }
    virtual void forward() = 0;
    virtual Matrix* backward(Matrix *error, int step) = 0;
    virtual ~Layer() {
        if (output != nullptr) {
            free_matrix(output);
        }
    }
    void changeDataSize(Matrix * inp){
        Matrix* t = create_matrix(inp->m, output->n);
        free_matrix(output);
        output = t;
        input = inp;
    }
};


#endif //DISTNET_LAYER_H

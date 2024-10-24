//
// Created by serdar on 10/23/24.
//

#include "NeuralNet.h"


NeuralNet::NeuralNet(Matrix *input, Loss *loss) {
    this->input = input;
    this->loss = loss;
}

Matrix *NeuralNet::get_final_output() {
    if (layers.size() == 0) {
        return input;
    } else {
        return layers[layers.size() - 1]->output;
    }
}

void NeuralNet::add_layer(Layer *layer) {
    layers.push_back(layer);
}

void NeuralNet::train(int epochs) {
    for (int i = 0; i < epochs; i++) {
        for (Layer* layer: layers) {
            layer->forward();
        }
        Matrix *error = loss->get_error_prime(get_final_output());
        for (int k = layers.size() - 1; k >= 0; k--) {
            error = layers[k]->backward(error, i);
        }
        free_matrix(error);
    }
}

void NeuralNet::test() {
    for (auto &layer: layers) {
        layer->forward();
    }
    loss->eval(get_final_output());
}


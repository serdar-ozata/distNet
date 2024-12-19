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
    double* starts = (double*) malloc(sizeof(double) * epochs);
    double* ends = (double*) malloc(sizeof(double) * epochs);
    for (int i = 0; i < epochs; i++) {
        starts[i] = MPI_Wtime();
        for (Layer* layer: layers) {
            layer->forward();
        }

        loss->eval(get_final_output(), false);
        Matrix *error = loss->get_error_prime(get_final_output());
        for (int k = layers.size() - 1; k >= 0; k--) {
            error = layers[k]->backward(error, i + 1); // step size shouldn't be 0
        }
        free_matrix(error);
        ends[i] = MPI_Wtime();
    }
    double avg_time = 0;
    for (int i = 0; i < epochs; i++) {
        avg_time += ends[i] - starts[i];
    }
    avg_time /= epochs;
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        printf("Average time for epoch: %f\n", avg_time);
    }
    free(starts);
    free(ends);
}

void NeuralNet::test(Matrix* features, Matrix* labels) {
    for (int i = 0; i < layers.size(); i++) {
        layers[i]->changeDataSize(features);
        features = layers[i]->output;
    }

    for (auto &layer: layers) {
        layer->forward();
    }
    loss->eval(get_final_output(), true);
}


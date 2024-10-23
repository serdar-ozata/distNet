//
// Created by serdar on 10/23/24.
//

#ifndef DISTNET_NEURALNET_H
#define DISTNET_NEURALNET_H
#include "layers/Layer.h"
#include "loss/Loss.h"
#include <vector>

enum run_mode {
    TRAIN,
    TEST
};
using namespace std;

class NeuralNet {
private:
    Matrix* input;
    Loss* loss;
public:
    vector<Layer*> layers;
    NeuralNet(Matrix *input, Loss* loss);
//    void change_input(Matrix *input); not important for now
    void train(int epochs);
    void test();
    Matrix *get_final_output(); // to bind to new layer
    void add_layer(Layer *layer);
};


#endif //DISTNET_NEURALNET_H

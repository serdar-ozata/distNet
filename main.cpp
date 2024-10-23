#include <csignal>
#include "src/NeuralNet.h"
#include "src/layers/FullyConnected.h"
#include "src/layers/ReLu.h"
#include "src/loss/SoftmaxCEntropyClassification.h"

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
//    sleep(10); // gdb
    Matrix *input = create_matrix(1, 2);
    matrix_fill(input, 1);
    Matrix *labels = create_matrix(1, 2);
    matrix_fill(labels, 1);
    auto *loss = new SoftmaxCEntropyClassification(labels);
    NeuralNet net(input, loss);

    FullyConnected fcn1(net.get_final_output(), 4);
    ReLu reLu1(net.get_final_output());
    FullyConnected fcn2(net.get_final_output(), 2);

    net.add_layer(&fcn1);
    net.add_layer(&reLu1);
    net.add_layer(&fcn2);

    net.train(3);
    printf("done\n");
    MPI_Finalize();
}

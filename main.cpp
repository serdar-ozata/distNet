#include <csignal>
#include "src/NeuralNet.h"
#include "src/layers/FullyConnected.h"
#include "src/layers/ReLu.h"
#include "src/loss/SoftmaxCEntropyClassification.h"
#include <iostream>
#include <fstream>

#include "src/util/io.h"
#include "src/loss/LogLoss.h"

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
//    sleep(5); // gdb
    std::ifstream features_csv("data/airline_passenger_satisfaction_x.csv");
    std::ifstream labels_csv("data/airline_passenger_satisfaction_y.csv");
    CSVMatrix mat1 = csv2Mat(readCSV(features_csv));
    CSVMatrix mat2 = csv2Mat(readCSV(labels_csv));
    Matrix *input = &(mat1.data);
    Matrix *labels = &(mat2.data);
    if (input->m != labels->m) {
        std::cerr << "The number of samples in the input and labels do not match ";
        std::raise(SIGABRT);
    }
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        printf("Input matrix: %d x %d\n", input->m, input->n);
    }
    auto *loss = new LogLoss(labels);
    NeuralNet net(input, loss);

    FullyConnected fcn1(net.get_final_output(), 10);
    net.add_layer(&fcn1);
    ReLu reLu1(net.get_final_output());
    net.add_layer(&reLu1);
    FullyConnected fcn2(net.get_final_output(), 5);
    net.add_layer(&fcn2);
    ReLu reLu2(net.get_final_output());
    net.add_layer(&reLu2);
    FullyConnected fcn3(net.get_final_output(), 1);
    net.add_layer(&fcn3);
    net.train(500);
    MPI_Finalize();
    return 0;
}

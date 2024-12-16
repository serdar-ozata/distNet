#include <csignal>
#include "src/NeuralNet.h"
#include "src/layers/FullyConnected.h"
#include "src/layers/ReLu.h"
#include "src/loss/SoftmaxCEntropyClassification.h"
#include <iostream>
#include <fstream>

#include "src/util/io.h"

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    // sleep(10); // gdb
    std::ifstream file1("moreboolets.csv");
    CSVMatrix mat1 = csv2Mat(readCSV(file1));
    // only process with id 0 will print
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
        std::cout << mat1 << std::endl;
    Matrix *input = &(mat1.data);
    // matrix_fill(input, 1);
    std::ifstream file2("biggerwepouns.csv");
    CSVMatrix mat2 = csv2Mat(readCSV(file2));
    if (rank == 0)
        std::cout << mat2 << std::endl;
    Matrix *labels = &(mat2.data);
    // matrix_fill(labels, 1);
    auto *loss = new SoftmaxCEntropyClassification(labels);
    NeuralNet net(input, loss);

    FullyConnected fcn1(net.get_final_output(), 4);
    ReLu reLu1(net.get_final_output());
    FullyConnected fcn2(net.get_final_output(), 2);

    net.add_layer(&fcn1);
    net.add_layer(&reLu1);
    net.add_layer(&fcn2);

    net.train(3);
    printf("%d done\n", rank);
    MPI_Finalize();
    std::cout << rank << " out" << std::endl;
    return 0;
}

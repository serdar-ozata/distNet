cmake_minimum_required(VERSION 3.22)
project(distNet)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -fopenmp")

find_package(MPI REQUIRED)

add_executable(distNet main.cpp
        src/layers/Layer.h
        src/Matrix.cpp
        src/Matrix.h
        src/layers/ReLu.h
        src/layers/ActivationLayer.h
        src/layers/LReLu.h
        src/layers/Dropout.h
        src/layers/FullyConnected.h
        src/layers/Convolutional.h
        src/NeuralNet.cpp
        src/NeuralNet.h
        src/util/io.h
        src/util/io.cpp
        src/loss/Loss.cpp
        src/loss/Loss.h
        src/loss/SoftmaxCEntropyClassification.h)

target_link_libraries(distNet m)
target_link_libraries(distNet  MPI::MPI_CXX)
target_link_libraries(distNet ${MPI_C_LIBRARIES})
target_include_directories(distNet PUBLIC ${MPI_C_INCLUDE_PATH})

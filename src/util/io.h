//
// Created by bsahin on 03/11/24.
//

#ifndef DISTNET_IO_H
#define DISTNET_IO_H
#include <iostream>
#include <string>
#include <vector>
#include "../Matrix.h"

struct CSVTable {
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> data;
};

struct CSVMatrix {
    std::vector<std::string> headers;
    Matrix data{ 0, 0, nullptr };


    CSVMatrix() = default;

    ~CSVMatrix() {
        for (int i = 0; i < data.m; i++) {
            free(data.data[i]);
        }
        free(data.data);
    }

    // copy ctor etc. (rule of 5)
    CSVMatrix(const CSVMatrix &other) {
        headers = other.headers;
        data.m = other.data.m;
        data.n = other.data.n;
        data.data = (double **) malloc(data.m * sizeof(double *));
        for (int i = 0; i < data.m; i++) {
            data.data[i] = (double *) malloc(data.n * sizeof(double));
            for (int j = 0; j < data.n; j++) {
                data.data[i][j] = other.data.data[i][j];
            }
        }
    }

    CSVMatrix& operator=(const CSVMatrix &other) {
        if (this == &other) {
            return *this;
        }
        for (int i = 0; i < data.m; i++) {
            free(data.data[i]);
        }
        free(data.data);
        headers = other.headers;
        data.m = other.data.m;
        data.n = other.data.n;
        data.data = (double **) malloc(data.m * sizeof(double *));
        for (int i = 0; i < data.m; i++) {
            data.data[i] = (double *) malloc(data.n * sizeof(double));
            for (int j = 0; j < data.n; j++) {
                data.data[i][j] = other.data.data[i][j];
            }
        }
        return *this;
    }

    CSVMatrix(CSVMatrix &&other) noexcept {
        headers = std::move(other.headers);
        data.m = other.data.m;
        data.n = other.data.n;
        data.data = other.data.data;
        other.data.data = nullptr;
    }

    CSVMatrix& operator=(CSVMatrix &&other) noexcept {
        if (this == &other) {
            return *this;
        }
        for (int i = 0; i < data.m; i++) {
            free(data.data[i]);
        }
        free(data.data);
        headers = std::move(other.headers);
        data.m = other.data.m;
        data.n = other.data.n;
        data.data = other.data.data;
        other.data.data = nullptr;
        return *this;
    }
};

CSVTable readCSV(std::istream &input);
CSVMatrix csv2Mat(const CSVTable &table);

//void writeCSV(std::ostream &output, const CSVTable &table); // might be unnecessary

std::ostream &operator<<(std::ostream &os, const CSVMatrix &mat); // output in CSV format

#endif //DISTNET_IO_H

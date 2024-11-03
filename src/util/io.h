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
    Matrix data;
};

CSVTable readCSV(std::istream &input);
CSVMatrix csv2Mat(const CSVTable &table);

//void writeCSV(std::ostream &output, const CSVTable &table); // might be unnecessary

#endif //DISTNET_IO_H

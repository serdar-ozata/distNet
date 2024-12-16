//
// Created by bsahin on 03/11/24.
//
#include "io.h"
#include <unordered_map>

using std::string;
CSVTable readCSV(std::istream& input) {
    const char sep = ',';
    CSVTable table;
    string line;
    if (input) {
        while (getline(input, line)) {
            std::vector<std::string> vec;
            size_t start = 0;
            size_t end = 0;
            while ((end = line.find(sep, start)) != std::string::npos) {
                vec.push_back(line.substr(start, end - start));
                start = end + 1;
            }
            vec.push_back(line.substr(start));
            if (table.headers.empty()) {
                table.headers = vec;
            } else {
                table.data.push_back(vec);
            }
        }
    }
    return table;
}

CSVMatrix csv2Mat(const CSVTable& table) {
    CSVMatrix csvmat;
    csvmat.headers = table.headers;
    // the matrix is row-major, and it is double**
    csvmat.data.m = table.data.size();
    csvmat.data.n = table.headers.size();
    csvmat.data.data = (double*) malloc(csvmat.data.m * csvmat.data.n * sizeof(double));
    for (int i = 0; i < csvmat.data.m; i++) {
        for (int j = 0; j < csvmat.data.n; j++) {
            csvmat.data.data[csvmat.data.n * i + j] = std::stod(table.data[i][j]);
        }
    }

    return csvmat;
}

std::ostream& operator<<(std::ostream& os, const CSVMatrix& mat) {
    // output in CSV format
    // output headers first
    for (int i = 0; i < mat.headers.size(); i++) {
        os << mat.headers[i];
        if (i < mat.headers.size() - 1) {
            os << ',';
        }
    }
    os << std::endl;
    for (int i = 0; i < mat.data.m; i++) {
        for (int j = 0; j < mat.data.n; j++) {
            os << mat.data.data[mat.data.n * i + j];
            if (j < mat.data.n - 1) {
                os << ',';
            }
        }
        os << '\n';
    }
    return os;
}



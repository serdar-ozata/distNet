//
// Created by bsahin on 03/11/24.
//
#include "io.h"
#include <unordered_map>
#include <mpi.h>

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
void getCSVRankIdx(const CSVTable &table, int& start, int& end) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int rows = table.data.size();
    int rows_per_proc = rows / size;
    int remainder = rows % size;
    if (rank < remainder) {
        start = rank * (rows_per_proc + 1);
        end = start + rows_per_proc + 1;
    } else {
        start = rank * rows_per_proc + remainder;
        end = start + rows_per_proc;
    }
}

CSVMatrix csv2Mat(const CSVTable& table) {
    int start, end;
    getCSVRankIdx(table, start, end);

    CSVMatrix csvmat;
    csvmat.headers = table.headers;
    // the matrix is row-major, and it is double**
    csvmat.data.m = end - start;
    csvmat.data.n = table.headers.size();
    csvmat.data.data = (double*) malloc(csvmat.data.m * csvmat.data.n * sizeof(double));
    for (int i = start; i < end; i++) {
        for (int j = 0; j < csvmat.data.n; j++) {
            try {csvmat.data.data[(i - start) * csvmat.data.n + j] = std::stod(table.data[i][j]);}
            catch (std::invalid_argument& e)
            {
                csvmat.data.data[(i - start) * csvmat.data.n + j] = 0;
            }
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



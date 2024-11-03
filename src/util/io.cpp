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
    return csvmat;
}



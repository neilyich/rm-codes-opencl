//
// Created by Илья Ильич on 18.12.2023.
//

#ifndef UNTITLED_UTILS_H
#define UNTITLED_UTILS_H

#include <fstream>
#include <sstream>

bool PRINT_ENABLED = false;

std::string readFile(const std::string& filename) {
    std::ifstream f(filename);
    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}

void print(const std::string& label, int* arr, int len) {
    if (!PRINT_ENABLED) {
        return;
    }
    std::cout << label << ": ";
    if (len <= (1 << 10)) {
        for (int i = 0; i < len; i++) {
            std::cout << arr[i] << ' ';
        }
    } else {
        std::cout << len << " elements...";
    }
    std::cout << std::endl;
}

#define microseconds std::chrono::milliseconds

#endif //UNTITLED_UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "linear_system_input.h"


std::vector<double> LinearSystemInput::get_equation(int rank, int equation_number) {
    std::vector<double> result;
    double buffer;
    std::cout << "Уравнение № " << equation_number << std::endl;
    for(int i = 1; i <= rank; ++i) {
        std::cout << "Коэффициент при X" << i << " = ";
        std::cin >> buffer;
        result.push_back(buffer);
    }
    std::cout << "Свободный член = ";
    std::cin >> buffer;
    result.push_back(buffer);
    return result;
}


void LinearSystemInput::read_equations() {
    std::cout << "Число уравнений = ";
    int rank;
    std::cin >> rank;
    for (int i = 1; i <= rank; ++i) {
        storage.push_back(get_equation(rank, i));
    }
}


int LinearSystemInput::get_rank() {
    return storage.size();
}


void LinearSystemInput::fill_buffer(double* buffer, int variable_index) {
    int buffer_index = 0;
    for (auto line: storage) {
        for (int i = 0; i < get_rank(); ++i) {
            buffer[buffer_index++] = variable_index == i + 1 ? line[get_rank()] : line[i];
        }
    }
}

void LinearSystemInput::read_equations_from_file(const char* filename) {
    std::ifstream infile(filename);
    int rank;
    double buffer;
    infile >> rank;
    for (int i = 1; i <= rank; ++i) {
        std::vector<double> row;
        for(int j = 0; j <= rank; ++j) {
            infile >> buffer;
            row.push_back(buffer);
        }
        storage.push_back(row);
    }
    infile.close();
}

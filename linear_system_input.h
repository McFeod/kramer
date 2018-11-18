#ifndef LINEAR_SYSTEM_INPUT_H
#define LINEAR_SYSTEM_INPUT_H
#include <vector>
#include <string>


class LinearSystemInput {
    private:
        std::vector<std::vector<double>> storage;
        std::vector<double> get_equation(int rank, int equation_number);

    public:
        void read_equations();
        void read_equations_from_file(const char* filename);
        int get_rank();
        void fill_buffer(double* buffer, int variable_index);
};

#endif
#include <cstdio>
#include "determinant.h"

int main(int argc, char* argv[]) {
    double elements[9] = {
        23, 48, -52,
        -24, -50, 50,
        46, 99, -98
    };

    printf("det = %f\n", omp_determinant(3, elements));

    return 0;
}

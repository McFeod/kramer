#include "determinant.h"
// #include "omp.h"
// #include <cstdio>


double determinant(AbstractSquareMatrix &matrix) {
    if (matrix.rank == 1) {
        return matrix.get(1, 1);
    }
    
    double sum = 0;
    int next_sign = 1;
    for (int i = 1; i <= matrix.rank; ++i) {
        SubMatrix submatrix(1, i, &matrix);
        sum += next_sign * determinant(submatrix) * matrix.get(1, i);
        next_sign = -next_sign;
    }

    return sum;
}


double omp_determinant(int rank, double* elements) {
    if (rank == 1) {
        return elements[0];
    }
    double sum = 0;

    #pragma omp parallel for reduction(+:sum) shared(elements, rank)
    for (int i = 1; i <= rank; ++i) {
        // printf("%d\n", omp_get_thread_num());
        SquareMatrix matrix(rank, elements);
        SubMatrix submatrix(1, i, &matrix);
        int sign = i % 2 ? 1 : -1;
        sum += sign * determinant(submatrix) * matrix.get(1, i);
    }
    return sum;
}

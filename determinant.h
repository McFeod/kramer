#ifndef DETERMINANT_H
#define DETERMINANT_H
#include "square_matrix.h"

double determinant(AbstractSquareMatrix &matrix);
double omp_determinant(int rank, double* elements);

#endif

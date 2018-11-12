#include <cassert>
#include "square_matrix.h"


AbstractSquareMatrix::AbstractSquareMatrix(int rank): rank(rank) {
    assert(rank > 0);
}

void AbstractSquareMatrix::check(int row, int column) {
    assert ((row > 0) && (row <= rank));
    assert ((column > 0) && (column <= rank));
}


SquareMatrix::SquareMatrix(int rank): AbstractSquareMatrix(rank) {
    representation = new double[rank];
    allocate = true;
}


SquareMatrix::SquareMatrix(int rank, double* items):
    AbstractSquareMatrix(rank),
    representation(items) {
    allocate = false;
}

SquareMatrix::~SquareMatrix() {
    if (allocate) {
        delete[] representation;
    }
}

int SquareMatrix::flat_index(int row, int column) {
    check(row, column);
    return (row - 1) * rank + column - 1;
}

double SquareMatrix::get(int row, int column) {
    return representation[flat_index(row, column)];
}

void SquareMatrix::set(int row, int column, double value) {
    representation[flat_index(row, column)] = value;
}


SubMatrix::SubMatrix(int row, int column, AbstractSquareMatrix *matrix):
    AbstractSquareMatrix(matrix->rank - 1),
    parent(matrix),
    exclude_row(row),
    exclude_column(column) {}

int SubMatrix::convert_index(int index, int excluded) {
    return index < excluded ? index : index + 1;
}

double SubMatrix::get(int row, int column) {
    return parent->get(
        convert_index(row, exclude_row),
        convert_index(column, exclude_column)
    );
}

void SubMatrix::set(int row, int column, double value) {
    parent->set(
        convert_index(row, exclude_row),
        convert_index(column, exclude_column),
        value
    );
}

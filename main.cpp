#include <iostream>
#include "determinant.h"
#include "linear_system_input.h"
#include "mpich/mpi.h"


const int TAG = 1;


int equation_to_task(int equation_number, int total) {
    return equation_number % (total - 1) + 1;
}


void master(int total) {
    LinearSystemInput input;
    input.read_equations_from_file("input.txt");

    int receiver;
    double det;
    int matrix_rank = input.get_rank();
    int buffer_size = matrix_rank * matrix_rank;
    auto matrix_buffer = new double[buffer_size];
    auto determinants = new double[matrix_rank];
    auto requests = new MPI_Request[matrix_rank];
    auto statuses = new MPI_Status[matrix_rank];

    MPI_Bcast(&matrix_rank, 1, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 1; i <= matrix_rank; ++i) {
        input.fill_buffer(matrix_buffer, i);
        receiver = equation_to_task(i, total);
        MPI_Send(matrix_buffer, buffer_size, MPI_DOUBLE, receiver, TAG, MPI_COMM_WORLD);
        MPI_Irecv(&determinants[i - 1], 1, MPI_DOUBLE, receiver, TAG, MPI_COMM_WORLD, &requests[i - 1]);
    }

    input.fill_buffer(matrix_buffer, 0);
    det = omp_determinant(matrix_rank, matrix_buffer);

    MPI_Waitall(matrix_rank, requests, statuses);

    if (det == 0) {
        std::cout << "Нет решений" << std::endl;
    } else {
        for (int i = 0; i < matrix_rank; ++i) {
            std::cout << "X" << i + 1 << " = " << determinants[i] / det << std::endl;
        }
    }

    delete [] requests;
    delete [] statuses;
    delete [] determinants;
    delete [] matrix_buffer;
}


void slave(int proc_number, int total) {
    MPI_Status status;
    int matrix_rank, buffer_size;
    double det;
    double *matrix_buffer;

    MPI_Bcast(&matrix_rank, 1, MPI_INT, 0, MPI_COMM_WORLD);
    buffer_size = matrix_rank * matrix_rank;
    matrix_buffer = new double[buffer_size];

    for (int i = 1; i <= matrix_rank; ++i) {
        if (proc_number == equation_to_task(i, total)) {
            MPI_Recv(matrix_buffer, buffer_size, MPI_DOUBLE, 0, TAG, MPI_COMM_WORLD, &status);
            det = omp_determinant(matrix_rank, matrix_buffer);
            MPI_Send(&det, 1, MPI_DOUBLE, 0, TAG, MPI_COMM_WORLD);
        }
    }

    delete [] matrix_buffer;
}


int main(int argc, char* argv[]) {
    int proc_number, total;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_number);
    MPI_Comm_size(MPI_COMM_WORLD, &total);
    if (proc_number == 0) {
        master(total);
    } else {
        slave(proc_number, total);
    }
    MPI_Finalize();
    return 0;
}

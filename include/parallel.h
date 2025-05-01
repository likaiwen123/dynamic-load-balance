// Author: Kaiwen Li
// Note: This file is part of the C++ library for the dynamic load balance algorithm.

#ifndef PARALLEL_H
#define PARALLEL_H

#include "mpi.h"

class Parallel {
public:
  int rank; // Process ID
  int size; // Number of processes
  bool is_master; // Is master process

  Parallel() {}

  void Init(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    is_master = (rank == 0);
  }
};

extern Parallel OParallel;

#endif // PARALLEL_H

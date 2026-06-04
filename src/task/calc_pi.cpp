// Author: Kaiwen Li
// Note: This file is part of the C++ library for the dynamic load balance algorithm.

#include "task/calc_pi.h"

void CalcPi::calc_pi_single() {
  ++n;
  // Generate random points and count how many are inside the unit circle
  double x = static_cast<double>(rand()) / RAND_MAX;
  double y = static_cast<double>(rand()) / RAND_MAX;
  if (x * x + y * y <= 1.0) {
    count++;
  }
}

double CalcPi::get_pi() {
  return 4.0 * count / n;
}

void CalcPi::collect_result() {
  int total_count = 0;
  int total_n = 0;
  MPI_Request reqs[2];
  MPI_Iallreduce(&count, &total_count, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD, &reqs[0]);
  MPI_Iallreduce(&n, &total_n, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD, &reqs[1]);
  MPI_Waitall(2, reqs, MPI_STATUSES_IGNORE);
  count = total_count;
  n = total_n;
}

// Calculate pi using the Monte Carlo method, serial version
// This function generates n random points in the unit square and counts how many are inside the unit circle
double calc_pi_serial(int n) {
#ifndef NDEBUG
  srand(time(nullptr));
#else
  srand(0);
#endif
  int count = 0;
  for (int i = 0; i < n; ++i) {
    double x = static_cast<double>(rand()) / RAND_MAX;
    double y = static_cast<double>(rand()) / RAND_MAX;
    if (x * x + y * y <= 1.0) {
      count++;
    }
  }
  return 4.0 * count / n;
}

// Calculate pi using the Monte Carlo method, parallel version
// This function generates n random points in the unit square and counts how many are inside the unit circle
double calc_pi_parallel(int n) {
  CalcPi calc_pi;
  int number = n / OParallel.size;
  number += OParallel.rank < n % OParallel.size ? 1 : 0;
  for (int i = 0; i < number; ++i) {
    calc_pi.calc_pi_single();
  }
  calc_pi.collect_result();
  return calc_pi.get_pi();
}

// This function is used to calculate pi in the load balance algorithm
// It is called by the LoadBalance class
void calc_pi_lb_calc(void *arg) {
  CalcPi *calc_pi = static_cast<CalcPi *>(arg);
  calc_pi->calc_pi_single();
}
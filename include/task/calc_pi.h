// Author: Kaiwen Li
// Note: This file is part of the C++ library for the dynamic load balance algorithm.

#ifndef CALC_PI_H
#define CALC_PI_H

#include <random>
#include <utility>
#include <vector>

#include "parallel.h"

class CalcPi {
protected:
  int count = 0; // Count of points inside the circle
  int n = 0; // Total number of points
public:
  // single step of the Monte Carlo method
  // - This function generates a random point (x, y) in the unit square
  void calc_pi_single();

  double get_pi();

  // Collect the results from all processes and sum them up
  // - This function uses MPI_Allreduce to sum the count and n variables across all processes
  // and store the results back in the count and n variables of the current process
  // - This is necessary to get the final count of points inside the circle and the total number of points generated
  // across all processes
  void collect_result();

  // This function is used to provide the details of the calculation
  std::string details() {
    return "Count: " + std::to_string(count) + ", Total Points: " + std::to_string(n);
  }
};

// Calculate pi using the Monte Carlo method, serial version
// This function generates n random points in the unit square and counts how many are inside the unit circle
double calc_pi_serial(int n);
  
// Calculate pi using the Monte Carlo method, parallel version
// This function generates n random points in the unit square among all the processes and counts how many are inside the unit circle
double calc_pi_parallel(int n);

// This function is used to calculate pi in the load balance algorithm
// It is called by the LoadBalance class
void calc_pi_lb_calc(void *arg);

#endif // CALC_PI_H

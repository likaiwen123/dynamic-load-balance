// Author: Kaiwen Li
// Note: This file is part of the C++ library for the dynamic load balance algorithm.

#include <random>
#include <iostream>
#include <ctime>

#include "parallel.h"
#include "lb.h"
#include "task/calc_pi.h"

Parallel OParallel;

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <number_of_samples> <time_interval>" << std::endl;
    return 1;
  }
  long long number_of_samples = std::stoll(argv[1]);
  double time_interval = std::stof(argv[2]);

  // Initialize MPI
  OParallel.Init(NULL, NULL);

#ifndef NDEBUG
  srand(time(nullptr) + OParallel.rank);
#else
  srand(OParallel.rank);
#endif

  // Example usage of LoadBalance
  LoadBalance lb(number_of_samples, time_interval);
  CalcPi calc_pi;
  // Dynamic load balance and calculation of pi
  lb.Run(calc_pi_lb_calc, &calc_pi);
  // Collect results from all processes
  calc_pi.collect_result();
  // Get the estimated value of pi
  double pi = calc_pi.get_pi();
  if (OParallel.is_master) {
    std::cout << "Estimated value of pi: " << pi << std::endl;
#ifndef NDEBUG
    std::cout << "Details: " << calc_pi.details() << std::endl;
#endif
  }

  MPI_Finalize();
  return 0;
}
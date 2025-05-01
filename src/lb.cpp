// Author: Kaiwen Li
// Note: This file is part of the C++ library for the dynamic load balance algorithm.

#include <iostream>

#include "lb.h"


bool LoadBalance::IsDone(long long target_number, long long cur_number, time_t *last_t) {
  time_t current_t = time(nullptr);
  if (current_t - *last_t >= time_interval) {
    *last_t = current_t;

#ifndef NDEBUG
    std::cout << "Proc: " << OParallel.rank << ", number: " << cur_number << std::endl;
#endif

    long long total;
    MPI_Allreduce(&cur_number, &total, 1, MPI_LONG_LONG_INT, MPI_SUM, MPI_COMM_WORLD);

#ifndef NDEBUG
    if (OParallel.is_master) {
      std::cout << "Total: " << total << ", time: " << current_t << std::endl;
    }
#endif

    if (total >= target_number) {
      if (OParallel.is_master) {
        std::cout << "Total: " << total << ", target: " << target_number << ", time: " << current_t << std::endl;
      }
      return true;
    } else {
      return false;
    }
  }
  return false;
}

void LoadBalance::Run(void (*func)(void *), void *arg) {
  time_t last_t = time(nullptr);
  long long cur_number = 0;

  while (!IsDone(target_number, cur_number, &last_t)) {
    func(arg);
    cur_number++;
  }
}

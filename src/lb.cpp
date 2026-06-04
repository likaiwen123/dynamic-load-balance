// Author: Kaiwen Li
// Note: This file is part of the C++ library for the dynamic load balance algorithm.

#include <iostream>

#include "lb.h"


LoadBalance::~LoadBalance() {
  if (reduce_pending_) {
    MPI_Wait(&reduce_request_, MPI_STATUS_IGNORE);
  }
}

bool LoadBalance::IsDone(long long target_number, long long cur_number, time_t *last_t) {
  // Check for completed non-blocking reduce
  if (reduce_pending_) {
    int flag = 0;
    MPI_Test(&reduce_request_, &flag, MPI_STATUS_IGNORE);
    if (flag) {
      reduce_pending_ = false;

#ifndef NDEBUG
      std::cout << "Proc: " << OParallel.rank << ", number: " << snapshot_ << std::endl;
      if (OParallel.is_master) {
        std::cout << "Total: " << reduce_result_ << ", time: " << time(nullptr) << std::endl;
      }
#endif

      if (reduce_result_ >= target_number) {
        if (OParallel.is_master) {
          std::cout << "Total: " << reduce_result_ << ", target: " << target_number << ", time: " << time(nullptr) << std::endl;
        }
        return true;
      }
      // Not done — fall through to check if we should post another reduce
    } else {
      // Reduce still in progress, keep working
      return false;
    }
  }

  // No pending reduce — check time interval
  time_t current_t = time(nullptr);
  if (current_t - *last_t >= time_interval) {
    *last_t = current_t;
    snapshot_ = cur_number;
    reduce_result_ = cur_number;
    MPI_Iallreduce(MPI_IN_PLACE, &reduce_result_, 1, MPI_LONG_LONG_INT, MPI_SUM, MPI_COMM_WORLD, &reduce_request_);
    reduce_pending_ = true;
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

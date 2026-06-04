// Author: Kaiwen Li
// Note: This file is part of the C++ library for the dynamic load balance algorithm.

#ifndef LB_H
#define LB_H

#include <ctime>

#include "parallel.h"

class LoadBalance {
protected:
  double time_interval; // Time interval for load balancing, seconds
  long long target_number; // Target number of simulated samples
  MPI_Request reduce_request_ = MPI_REQUEST_NULL; // Non-blocking reduce request
  long long reduce_result_ = 0; // Result buffer for non-blocking reduce
  long long snapshot_ = 0; // Local count snapshot when reduce was posted
  bool reduce_pending_ = false; // Whether a non-blocking reduce is in flight
  time_t start_time_ = 0; // Wall-clock time when Run() started
  // Function to check if the target number of samples has been reached
  bool IsDone(long long target_number, long long cur_number, time_t *last_t);
public:
  LoadBalance(long long target_number, double interval = 1.0) : target_number(target_number), time_interval(interval) {}

  void SetTimeInterval(int interval) {
    time_interval = interval;
  }

  int GetTimeInterval() const {
    return time_interval;
  }

  void Run(void (*func)(void *), void *arg);
};

#endif // LB_H

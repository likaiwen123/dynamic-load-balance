# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

A C++17 MPI-based time-based dynamic load balance library. Distributes tasks across MPI worker processes by periodically checking global progress at a configurable time interval. The included demo uses Monte Carlo π estimation to validate correctness.

## Build & Run

Requires: MPI implementation, C++17 compiler, CMake ≥ 3.10.

```bash
mkdir -p build && cd build
cmake ..                           # Release build (default)
cmake -DCMAKE_BUILD_TYPE=Debug ..  # Debug build (enables per-process progress output)
make
mpirun -np <N> ./bin/dlb <sample_count> <time_interval_seconds>
# Example: mpirun -np 10 ./bin/dlb 1000000000 1
```

Binary output is at `build/bin/dlb`.

## Architecture

**Execution model:** All MPI ranks run the same loop (`LoadBalance::Run`). Every `time_interval` seconds, `MPI_Allreduce` sums each rank's local task count. Once the global total reaches `target_number`, all ranks exit simultaneously — no master/worker dispatch, no task stealing.

**Key classes:**
- `Parallel` (`include/parallel.h`) — singleton `OParallel` wrapping MPI init/rank/size. Initialized once in `main.cpp`.
- `LoadBalance` (`include/lb.h`, `src/lb.cpp`) — core loop. `Run(func, arg)` repeatedly calls `func` and checks `IsDone()` which does the periodic `MPI_Allreduce` barrier.
- Task classes (e.g. `CalcPi` in `include/task/calc_pi.h`) — provide a single-step function and a `collect_result()` that aggregates across ranks via `MPI_Allreduce`.

**To integrate a custom task:** Replace `calc_pi_lb_calc` with a `void func(void*)` wrapping your per-step work. Your task class needs a `collect_result()` method that uses `MPI_Allreduce` to sum partial results across ranks.

## Code Conventions

- Global `OParallel` instance defined in `src/main.cpp`, declared `extern` in `include/parallel.h`.
- Debug output guarded by `#ifndef NDEBUG` — only appears in Debug builds.
- RNG seeding: Debug uses `srand(time + rank)` for randomness; Release uses `srand(rank)` for reproducibility.
- All source files carry `Author: Kaiwen Li` header comments.

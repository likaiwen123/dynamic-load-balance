# Time-based Dynamic Load Balance
This is a demonstrating implementation of a time-based dynamic load balance algorithm.

The algorithm is designed to distribute tasks among multiple workers based on the time taken to complete each task. The goal is to ensure that all workers are utilized efficiently and that no worker is idle while others are overloaded.

## How to Use
0. Prerequisites
   - MPI (Message Passing Interface) installed on your system.
   - C++ compiler (e.g., g++).
   - CMake (for building the project).
1. Clone the repository:
   ```bash
   git clone https://github.com/likaiwen123/dynamic-load-balance.git
   cd dynamic-load-balance
   ```
2. Build the project:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```
3. Run the program:
   ```bash
   mpirun -np <number_of_processes> ./bin/dlb <task_count> <time_interval>
   ```
   Replace `<number_of_processes>` with the number of worker processes you want to use, `<task_count>` with the total number of tasks to be distributed, and `<time_interval>` with the time interval for task distribution.
4. Monitor the output:
    The program will output the number of tasks taken by each worker, and the final guess of PI.
5. Clean up:
    ```bash
    make clean
    ```

## Example
```bash
mpirun -np 10 ./bin/dlb 1000000000 1
```
This command will run the program with 10 worker processes, distributing 1 billion tasks with a time interval of 1 second.

When using `-DCMAKE_BUILD_TYPE=Debug`, the program will run in debug mode, and the expected output will be like:
```
Proc: 0, number: 23193088
Total: 239474009, elapsed: 1s
Proc: 1, number: 20442726
Proc: 2, number: 23563259
Proc: 3, number: 22097033
Proc: 4, number: 25706527
Proc: 5, number: 22532128
Proc: 6, number: 24855907
Proc: 7, number: 25695998
Proc: 8, number: 25669170
Proc: 9, number: 25718173
Proc: 0, number: 69387874
Total: 689176430, elapsed: 2s
Proc: 1, number: 57907271
Proc: 2, number: 70958621
Proc: 3, number: 68017159
Proc: 4, number: 72540199
Proc: 5, number: 61355300
Proc: 6, number: 70934737
Proc: 7, number: 72708593
Proc: 8, number: 72657049
Proc: 9, number: 72709627
Proc: 0, number: 115533704
Total: 1136295360, elapsed: 3s
Total: 1136295360, target: 1000000000, elapsed: 3s
Proc: 1, number: 96565845
Proc: 2, number: 117715846
Proc: 3, number: 111369477
Proc: 4, number: 113676086
Proc: 5, number: 105893316
Proc: 6, number: 116518755
Proc: 7, number: 119708524
Proc: 8, number: 119667787
Proc: 9, number: 119646020
Estimated value of pi: 3.14154
Total samples: 1136295360 / target: 1000000000, elapsed: 3s
```

## How to Integrate in Your Project

In fact, the `main.cpp` file is a demonstration of how to use the `LoadBalance` class for calculating PI with Monte Carlo method. You may substitute the `calc_pi_lb_calc` function with your own task function, and the `LoadBalance` class will handle the load balancing for you. Additionally, a result collection function like `collect_result` of class `CalcPi` is required to gather the results from all processes.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

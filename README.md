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
Proc: 0, number: 24032074
Proc: 1, number: 26072203
Proc: 2, number: 22901262
Proc: 3, number: 28590375
Proc: 4, number: 22551952
Proc: 5, number: 27359534
Proc: 6, number: 28411414
Proc: 7, number: 28593060
Proc: 8, number: 24832572
Proc: 9, number: 24553017
Total: 257897463, time: 1780554658
Proc: 0, number: 65968665
Proc: 1, number: 71815840
Proc: 2, number: 60989693
Proc: 3, number: 75987360
Proc: 4, number: 59658148
Proc: 5, number: 71582220
Proc: 6, number: 75385086
Proc: 7, number: 75886959
Proc: 8, number: 62246697
Proc: 9, number: 68462385
Total: 687983053, time: 1780554659
Proc: 0, number: 105934037
Proc: 1, number: 119227576
Proc: 2, number: 101125274
Proc: 3, number: 122371478
Proc: 4, number: 96793472
Proc: 5, number: 117006955
Proc: 6, number: 121092413
Proc: 7, number: 123267606
Proc: 8, number: 99700136
Proc: 9, number: 115461133
Total: 1121980080, time: 1780554660
Total: 1121980080, target: 1000000000, time: 1780554660
Estimated value of pi: 3.14157
```

## How to Integrate in Your Project

In fact, the `main.cpp` file is a demonstration of how to use the `LoadBalance` class for calculating PI with Monte Carlo method. You may substitute the `calc_pi_lb_calc` function with your own task function, and the `LoadBalance` class will handle the load balancing for you. Additionally, a result collection function like `collect_result` of class `CalcPi` is required to gather the results from all processes.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

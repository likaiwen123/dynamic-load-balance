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
Proc: 0, number: 35026905
Total: 419409272, elapsed: 1s
Proc: 1, number: 38749643
Proc: 2, number: 43660371
Proc: 3, number: 39140101
Proc: 4, number: 41997399
Proc: 5, number: 44250291
Proc: 6, number: 43877483
Proc: 7, number: 44100546
Proc: 8, number: 44288064
Proc: 9, number: 44318469
Proc: 0, number: 82126249
Total: 870758880, elapsed: 2s
Proc: 1, number: 79111949
Proc: 2, number: 90689803
Proc: 3, number: 76541942
Proc: 4, number: 87432813
Proc: 5, number: 89978695
Proc: 6, number: 90316295
Proc: 7, number: 91523556
Proc: 8, number: 91289089
Proc: 9, number: 91748489
Proc: 0, number: 129537082
Total: 1320519364, elapsed: 3s
Total: 1320519364, target: 1000000000, elapsed: 3s
Proc: 1, number: 126446268
Proc: 2, number: 137713734
Proc: 3, number: 115836723
Proc: 4, number: 130863300
Proc: 5, number: 128953338
Proc: 6, number: 134396594
Proc: 7, number: 138935416
Proc: 8, number: 138718327
Proc: 9, number: 139118582
Estimated value of pi: 3.14165
Total samples: 1000000000, elapsed: 3s
```

## How to Integrate in Your Project

In fact, the `main.cpp` file is a demonstration of how to use the `LoadBalance` class for calculating PI with Monte Carlo method. You may substitute the `calc_pi_lb_calc` function with your own task function, and the `LoadBalance` class will handle the load balancing for you. Additionally, a result collection function like `collect_result` of class `CalcPi` is required to gather the results from all processes.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

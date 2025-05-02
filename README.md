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
   git clone
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

When using `-CMAKE_BUILD_TYPE=Debug`, the program will run in debug mode, and the expected output will be like:
```
Proc: 0, number: 26556919
Proc: 1, number: 26208717
Proc: 2, number: 22808399
Proc: 3, number: 26352186
Proc: 4, number: 21189604
Proc: 5, number: 20906653
Proc: 6, number: 26360280
Proc: 7, number: 26794059
Proc: 8, number: 24669451
Proc: 9, number: 26555157
Total: 248401425, time: 1746117829
Proc: 0, number: 74039302
Proc: 1, number: 73671368
Proc: 2, number: 70290092
Proc: 4, number: 59063632
Proc: 5, number: 58298794
Proc: 6, number: 73853971
Proc: 7, number: 74693724
Proc: 8, number: 62462128
Proc: 9, number: 74034788
Total: 694247583, time: 1746117830
Proc: 3, number: 73839784
Proc: 0, number: 121468994
Total: 1140059198, time: 1746117831
Total: 1140059198, target: 1000000000, time: 1746117831
Proc: 1, number: 121132524
Proc: 2, number: 117773915
Proc: 3, number: 121346437
Proc: 4, number: 96938481
Proc: 5, number: 95701855
Proc: 6, number: 121331881
Proc: 7, number: 122599993
Proc: 8, number: 100243779
Proc: 9, number: 121521339
Estimated value of pi: 3.14157
```

## How to Integrate in Your Project

In fact, the `main.cpp` file is a demonstration of how to use the `DynamicLoadBalance` class for calculating PI with Monte Carlo method. You may substitute the `calc_pi_lb_calc` function with your own task function, and the `DynamicLoadBalance` class will handle the load balancing for you. Additionally, a result collection function like `collect_result` of class `CalcPi` is required to gather the results from all processes.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

# Multithreading: Comparison of c11_threads and open_mp

This repository combines two parallel programming assignments into a single project. It contains the following directories:

* `c11_threads`: This directory contains the code which utilizes C11 threads for parallel execution.
* `open_mp`: This directory contains the code which utilizes OpenMP for parallel execution.

## Project Description

This project explores different approaches to parallel programming by implementing solutions to the same problem using two different parallel programming paradigms: C11 threads and OpenMP. The goal is to compare and contrast the implementation, performance, and complexity of these two approaches.

### c11\_threads

The `c11_threads` directory contains a solution using the C11 threads library. This approach involves explicit thread management, including thread creation, synchronization, and termination.  Key aspects of this implementation may include:

* Thread creation and management using `thrd_create`, `thrd_join`, and related functions.
* Synchronization mechanisms such as mutexes (`mtx_t`) and condition variables (`cnd_t`) to protect shared resources and coordinate thread execution.
* Careful handling of thread arguments and return values.

### open\_mp

The `open_mp` directory contains a solution using OpenMP.  OpenMP provides a higher-level abstraction for parallel programming, allowing for easier parallelization of code regions, loops, and other constructs. Key aspects of this implementation may include:

* Compiler directives (pragmas) to specify parallel regions, work-sharing constructs (e.g., `for`, `sections`), and synchronization.
* Runtime library functions for controlling the number of threads and other aspects of OpenMP execution.
* Implicit thread management by the OpenMP runtime.

## Repository Structure

The repository is organized as follows:

Multithreading/|-- README.md|-- c11_threads/|   |-- src/|   |   |-- (C source files)|   |-- include/|   |   |-- (Header files)|   |-- Makefile|-- open_mp/|   |-- src/|   |   |-- (C/C++ source files)|   |-- Makefile
## Build Instructions

### Makefile

1.  Navigate to the desired directory (open_mp or c11 threads)
2.  Ensure you have a compiler with OpenMP support (e.g., GCC with `-fopenmp`).
3.  Run `make`: to compile all
 - make primes: to run the python script to create the text files containing prime numbers 
 - make csv: to create the csv file containing averages
 - make clean: destroy executables and csv files

\Notes about the Makefile:

- the Makefile references python, not python3
- the Makefile uses UNIX commands, and therefore make clean only works from a linux shell, not windows powershell


## Running the Code

The executables will be located in the respective `c11_threads` and `open_mp` directories after building.  Run them from the command line.


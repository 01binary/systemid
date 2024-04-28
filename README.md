# System Identification Demo

This is a companion repository for an article about the Kalman filter.

We identify a system by using System Identification app in Matlab from [input.csv](./input.csv) file, using a discrete state-space model:

```
% Predict
y = Cx + Du + e

% Update state
x = Ax + Bu + Ke
```

Sample code in this repository then demonstrates how to use these two equations in practice for simulation and prediction.

The code is provided in Matlab (.m) and C++ (.cpp). Since Matlab is essentially a Python REPL, it should be easy to convert the Matlab script to Python.

## Matlab

Launch Matlab, set current directory to this repository, then execute `simulate.m` simply by typing `simulate` into Matlab prompt and pressing ENTER.

## C++

The C++ example can be built and executed with the following steps.

## Installation

+ Download [Eigen 3.4](https://gitlab.com/libeigen/eigen/-/releases/3.4.0)
+ Extract and change into the folder: `cd eigen-3.4.0`
+ Create a build folder: `mkdir build && cd build`
+ Setup CMake: `cmake ..`
+ Install: `make install`

## Building

+ Create a build folder: `mkdir build && cd build`
+ Setup CMake: `cmake ..`
+ Build: `make`
+ This should create `simulate` executable in `build` folder

## Running

Run the demo from the current directory:

```
./build/simulate
```

This will read inputs from `input.csv` and write filtered result into `output.csv`.

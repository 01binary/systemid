# System Identification Demo

This is a companion repository for an article about the Kalman filter.

In the article we identify a discrete linear state-space system by using System Identification app in Matlab from [input.csv](./input.csv) file:

```
% Predict
y = Cx + Du

% Update state
x = Ax + Bu
```

Sample code in this repository then demonstrates how to use these two equations in practice to simulate the system.

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

> Note: C++ 11 is required because matrix initialization shorthands are only supported by Eigen library on this standard. This is why `CMakeLists.txt` includes this line: `set(CMAKE_CXX_STANDARD 11)`.

## Building

+ Configure: `cmake .`
+ Build: `make`
+ This should create `kalman` executable

## Running

Run the demo from the current directory:

```
./kalman
```

This will read inputs from `input.csv` and write filtered result into `output.csv`.

## Debugging

Re-configure the build to add symbols and launch with LLDB debugger:

+ Setup CMake: `cmake . -DCMAKE_BUILD_TYPE=Debug`
+ Build: `make`
+ Open this folder in VSCode
+ Switch to Debug tab
+ Click Debug on *(lldb) Launch* configuration

The following steps were used to configure debugging in VSCode:

+ Switch to Debug tab
+ Click *create a launch.json file* link
+ Select *C++ (GDB/LLDB)*
+ Click *Add Configuration* on bottom right
+ Select *C/C++ (lldb) Launch*
+ A new entry should have been added to `launch.json`
+ Set `program` to `"${workspaceFolder}/kalman"`

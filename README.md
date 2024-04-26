# System Identification Demo

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
+ This should create `systemid` executable in build folder

## Running

Run the demo from the current directory:

```
./build/systemid
```

This will read inputs from `input.csv` and write filtered result into `output.csv`.

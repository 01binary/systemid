// Example of third order system model
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <limits>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// A weights (3x3 matrix)
const MatrixXd A
{
  {  0.0356,   -3.4131,  -14.9525 },
  { -1.0591,   85.8128,  334.3098 },
  {  1.5729,  -95.1123, -175.5517 }
};

// B weights (3x1 vector)
const RowVectorXd B {{ -0.0019, 0.0403, -0.0225 }};

// C weights (1x3 vector)
const VectorXd C {{ -5316.9, 24.87, 105.92 }};

// D weight (scalar)
const double D = 0;

// K weights (3x1 vector)
const RowVectorXd K {{ -0.0025, -0.0582, 0.0984 }};

// x0 initial state (3x1 vector)
const RowVectorXd x0 {{ -0.0458, 0.0099, -0.0139 }};

// Disturbance
const double DISTURBANCE_MEAN = 0.0;
const double DISTURBANCE_VAR = 841.9616;

// Files
const char* INPUT = "input.csv";
const char* OUTPUT = "output.csv";

// Cx + Du + e
double systemModel(
  const RowVector3d& x, double u, double e)
{
  return
    // Add contribution of state
    (C * x).sum() +
    // Add contribution of input
    D * u +
    // Add disturbance
    e;
}

// Ax + Bu + Ke
RowVectorXd systemState(
  const RowVectorXd& x, double u, double e)
{
  return
    // Add contribution of state
    x * A +
    // Add contribution of input
    B * u +
    // Add contribution of disturbance
    K * e;
}

bool openOutput(const string& path, ofstream& file)
{
  // Delete if exists
  std::remove(OUTPUT);

  file.open(path);
  if (!file.is_open()) return false;

  // Write output headers
  file << "time,prediction,measurement" << endl;

  return true;
}

bool openInput(const string& path, ifstream& file)
{
  file.open(path);
  if (!file.is_open()) return false;

  // Skip headers
  string headers;
  getline(file, headers);

  return true;
}

void read(ifstream& file, double& time, double& measurement, double& input, double& timeStep)
{
  static string line;
  static double lastTime = numeric_limits<double>::infinity();

  getline(file, line);
  sscanf(line.c_str(), "%lf, %lf, %lf", &time, &measurement, &input);

  timeStep = lastTime == numeric_limits<double>::infinity()
    ? 0.0
    : lastTime - time;

  lastTime = time;
}

int main(int argc, char** argv)
{
  // Open input
  ifstream inputFile;

  if (!openInput(INPUT, inputFile))
  {
    cerr << "Failed to open input file" << endl;
    return 1;
  }

  // Open output
  ofstream outputFile;

  if (!openOutput(OUTPUT, outputFile))
  {
    cerr << "Failed to open output file" << endl;
    return 1;
  }

  // Disturbance
  random_device rd;
  mt19937 gen(rd());
  normal_distribution<double> dist(
    DISTURBANCE_MEAN, DISTURBANCE_VAR);

  // System state
  RowVectorXd x = x0;

  // Simulation
  while(!inputFile.eof())
  {
    // Input
    double time, measurement, input, timeStep;
    read(inputFile, time, measurement, input, timeStep);

    // Simulate disturbance
    double e = dist(gen);

    // Predict
    double prediction = systemModel(x, input, e);

    // Update state
    x = systemState(x, input, e) * timeStep;

    // Output
    outputFile << time << "," << prediction << "," << measurement << endl;
  }

  return 0;
}

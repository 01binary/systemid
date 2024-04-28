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
  { 0.998800,   0.05193, -0.02261 },
  { 0.0222200, -0.01976,  0.7353  },
  { 0.0009856, -0.20930, -0.5957  }
};

// B weights (3x1 vector)
const RowVectorXd B {{
  -0.00000266,
  0.0000572747,
  -0.0001872152
}};

// C weights (1x3 vector)
const VectorXd C {{
  -5316.903919,
  24.867656,
  105.92416
}};

// D weight (scalar)
const double D = 0;

// K weights (3x1 vector)
const RowVectorXd K {{
  -0.0001655,
  -0.001508,
  6.209e-06
}};

// Initial state (3x1 vector)
const RowVectorXd x0 {{
  -0.0458,
  0.0099,
  -0.0139
}};

// Disturbance variance
const double ed = 2.239914935143708e+02;

// Files
const char* INPUT = "input.csv";
const char* OUTPUT = "output.csv";

double systemModel(RowVector3d& x, double u, double e)
{
  // y = Cx + Du + e
  double y =
    // Add contribution of state
    C.dot(x) +
    // Add contribution of input
    D * u +
    // Add disturbance
    e;

  // x = Ax + Bu + Ke
  x = x * A + B * u + K * e;
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
  normal_distribution<double> dist(0.0, ed);

  // System state
  RowVectorXd x = x0;

  // Simulation
  while(!inputFile.eof())
  {
    // Input
    double time, measurement, input, timeStep;
    read(inputFile, time, measurement, input, timeStep);

    // Predict
    double prediction = systemModel(x, input, dist(gen));

    // Output
    outputFile << time << "," << prediction << "," << measurement << endl;
  }

  return 0;
}

//
// Includes
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <Eigen/Dense>

//
// Namespaces
//

using namespace std;
using namespace Eigen;

//
// Constants
//

// A weights (3x3 matrix)
const MatrixXd A
{
  { -0.1199, 2.0558, 1.1026 },
  { -1.8226, -0.7465, -15.0483 },
  { 0.7375,  8.2928,  -16.6951 }
};

// B weights (3x1 vector)
const RowVectorXd B {{ 0.0009, 0.1359, 0.3223 }};

// C weights (1x3 vector)
const VectorXd C {{ -32.1738, -0.7282, 0.1308 }};

// D weight (scalar)
const double D = 8.7666e-04;

// K weights (3x1 vector)
const RowVectorXd K {{ -1.3722, -4.1560, 12.5563 }};

// x0 initial state (3x1 vector)
const RowVectorXd x0 {{ 0.0, 0.0, 0.0 }};

// Disturbance
const double DISTURBANCE_MEAN = 0.0;
const double DISTURBANCE_VAR = 841.9616;

//
// Functions
//

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
    A * x +
    // Add contribution of input
    B * u +
    // Add contribution of disturbance
    K * e;
}

bool openOutput(const string& path, ofstream& file)
{
  file.open(path);
  return file.is_open();
}

bool openInput(const string& path, ifstream& file)
{
  file.open(path);
  return file.is_open();
}

int main(int argc, char** argv)
{
  // Open input
  ifstream input;

  if (!openInput("input.csv", input))
  {
    cerr << "Failed to open input file" << endl;
    return 1;
  }

  // Open output
  ofstream output;

  if (!openOutput("output.csv", output))
  {
    cerr << "Failed to open output file" << endl;
    return 1;
  }

  // Disturbance
  random_device rd;
  mt19937 gen(rd());
  normal_distribution<double> dist(
    DISTURBANCE_MEAN, DISTURBANCE_VAR);

  // Kalman filter
  RowVectorXd x = x0;
  string line;
  double lastTime = 0.0;

  // Skip headers
  getline(input, line);

  while(!input.eof())
  {
    // Read time, input, output
    double time, u, y;
    getline(input, line);
    sscanf(line.c_str(), "%lf, %lf, %lf", &time, &u, &y);

    // Calculate time step
    double timeStep = lastTime - time;
    lastTime = time;

    // Predict
    double estimate = systemModel(x, u, 0.0);

    // Update state
    x = systemState(x, u, 0.0);

    output << estimate << endl;
  }

  return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

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

// Cx + Du + e
double systemPositionModel(
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
double systemVelocityModel(
  const RowVectorXd& x, double u, double e)
{
  RowVectorXd dxdt =
    // Add contribution of state
    A * x +
    // Add contribution of input
    B * u +
    // Add contribution of disturbance
    K * e;

  // Sum contributions
  return dxdt.block(0, 0, B.rows(), B.cols()).sum();
}

/*
while (getline(file, ID, ',')) {
    cout << "ID: " << ID << " " ; 

    getline(file, nome, ',') ;
    cout << "User: " << nome << " " ;

    getline(file, idade, ',') ;
    cout << "Idade: " << idade << " "  ; 

    getline(file, genero);
    cout << "Sexo: " <<  genero<< " "  ;
}
*/

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

  // Skip headers
  string headers;
  getline(input, headers);

  // Simulate
  RowVectorXd x {{ 0.0, 0.0, 0.0 }};
  string line;

  while(!input.eof())
  {
    double t = 0.0;
    double y = 0.0;
    double u = 0.0;

    getline(input, line);

    output << y << endl;
  }

  return 0;
}

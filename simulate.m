% A weights (3x3 matrix)
A = [ ...
  0.0356,   -3.4131,  -14.9525;
  -1.0591,   85.8128,  334.3098;
  1.5729,  -95.1123, -175.5517;
];

% B weights (3x1 vector)
B = [ ...
  -0.0019;
  0.0403;
  -0.0225;
];

% C weights (1x3 vector)
C = [ -5316.9, 24.87, 105.92 ];

% D weight (scalar)
D = 0;

% K weights (3x1 vector)
K = [ ...
  -0.0025;
  -0.0582;
  0.0984;
];

% Initial state (3x1 vector)
x0 = [ ...
  -0.0458;
  0.0099;
  -0.0139;
];

% Read input file
csv = readmatrix('https://raw.githubusercontent.com/01binary/systemid/main/input.csv');
time = csv(:,1);
measurement = csv(:,2);
input = csv(:,3);

% Simulate
x = x0;
timeStep = 0.02;
output = zeros(length(input), 1);

for i = 1:length(input)
  u = input(i);
  [y, dx] = systemModel(A, B, C, D, K, x, u, 0);
  x = x + dx * timeStep;
  output(i) = y;
end

% Plot against original measurements
plot(time, measurement, time, output);

function [y, dx] = systemModel(A, B, C, D, K, x, u, e)
  % y = Cx + Du + e
  y = ...
    C * x + ...  % Add contribution of state
    D * u + ...  % Add contribution of input
    e;           % Add disturbance

  % x = Ax + Bu + Ke
  dx = ...
    A * x + ... % Add contribution of state
    B * u + ... % Add contribution of input
    e * K;      % Add contribution of disturbance
end

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
D = 0.05;

% K weights (3x1 vector)
K = [ ...
  -0.0025;
  -0.0582;
  0.0984;
];

% Initial state
x0 = [ ...
  -0.0458;
  0.0099;
  -0.0139;
];

% Read input file
csv = readmatrix('input.csv');

% Select column vectors
time = csv(:,1);
measurement = csv(:,2);
input = csv(:,3);

% Simulate
x = x0;
output = zeros(length(time), 1);

for i = 1:length(time)
  if i > 1
    timeStep = time(i) - time(i-1);
  else
    timeStep = 0;
  end

  u = input(i);
  y = systemModel(x, u, 0, C, D);
  x = systemState(x, u, 0, A, B, K) * timeStep;

  output(i) = y;
end

function prediction = systemModel(x, u, e, C, D)
  prediction = ...
    sum(C * x) + ...  % Add contribution of state
    D * u + ...       % Add contribution of input
    e;                % Add contribution of disturbance
end

function x1 = systemState(x0, u, e, A, B, K)
  x1 = ...
    A * x0 + ...      % Add contribution of state
    B * u + ...       % Add contribution of input
    e * K;            % Add contribution of disturbance
end

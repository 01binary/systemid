global A;
global B;
global C;
global D;

% A weights (3x3 matrix)
A = [ ...
  0.9988,     0.05193, -0.02261;
  0.02222,   -0.01976,  0.7353;
  0.0009856, -0.2093,  -0.5957;
];

% B weights (3x1 vector)
B = [ ...
  -0.00000266;
  0.0000572747;
  -0.0001872152;
];

% C weights (1x3 vector)
C = [ ...
  -5316.903919, ...
  24.867656, ...
  105.92416 ...
];

% D weight (scalar)
D = 0;

% Initial state (3x1 vector)
initialState = [ ...
  -0.0458;
  0.0099;
  -0.0139;
];

% Read input
csv = readmatrix('https://raw.githubusercontent.com/01binary/systemid/main/input.csv');
time = csv(:,1);
measurements = csv(:,2);
inputs = csv(:,3);
outputs = zeros(length(inputs), 1);

% Simulate
state = initialState;

for i = 1:length(inputs)
  input = inputs(i);
  [prediction, state] = systemModel(state, input);
  outputs(i) = prediction;
end

% Plot
plot(time, measurements, time, outputs);

% Linear discrete system model
function [y, x] = systemModel(x, u)
  global A;
  global B;
  global C;
  global D;

  % y = Cx + Du
  y = ...
    C * x + ... % Map state to output
    D * u;      % Map input to output

  % x = Ax + Bu
  x = ...
    A * x + ... % Transition state
    B * u;      % Control state
end

clear
close all
clc


% initialize 
x = 1;
y = [1.525591201, 1.665477731, 1.818190922, 1.984906893, 2.166909606, 2.365600753, 2.582510552, 2.819309532, 3.077821397];

h_1 = .1;
h_2 = .2;
h_4 = .4;

%% trapezoidal rule
for 
    
   f(x) = 0.6345*exp(.8773*x);
   x = x + .1;

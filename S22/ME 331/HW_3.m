clear all 
clc

% HW 3 Problem 5

%% initialize
T = [500,600, 500, 600];
P = [2,2.5, 2, 2.5];
v1 = .17568;
u1 = 3116.9;
h1 = 3468.3;
s1 = 7.4337;

v2 = .19962;
u2 = 3291.5;
h2 = 3690.7;
s2 = 7.7043;

v3 = .13999;
u3 = 3112.8;
h3 = 3462.8;
s3 = 7.3254;

v4 = .15931;
u4 = 3288.5;
h4 = 3686.8;
s4 = 7.5979;



v = [v1, v2, v3, v4];
u = [u1, u2, u3, u4];
h = [h1, h2, h3, h4];
s = [s2, s2, s3, s4];

%% interpolate

interp = interp3(v,T,P,575,2.34);



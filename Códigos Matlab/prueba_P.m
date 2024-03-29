%%
%Sergio Gonzalez Muriel
%Degree thesis:  Reinforcement learning for object manipulation by a robotic arm
%%
% Test code for working with transformation matrices
P = [554.25 0 320.5 0;
    0 554.25 240.5 0;
    0 0 1 0];
P2I = [1 0 0;
       0 -1 481;
       0 0 1];
% S2B = [ 0 1 0 -0.030;
%         0 0 1 -0.140;
%         1 0 0 -0.110;
%         0 0 0 1];
S2B = [ 0 0 1 -73.4;
        -1 0 0 -12.5;
        0 1 0 -244.8;
        0 0 0 1];
T05 = [ 0 0 1 0.1905;
        0 -1 0 0;
        1 0 0 0.1450;
        0 0 0 1];
P_Inv = pinv(P);
I2P = inv(P2I);
I2S = pinv(P2I * P);
zero = P2I * P * [0,0,0,1]';
oneX = P2I * P * [1,0,0,1]';
oneY = P2I * P * [0,0.1,0,1]';
oneZ = P2I * P * [0,0,0.1,1]';
test4 = P2I * P * [0.4,0.6,0,1]';
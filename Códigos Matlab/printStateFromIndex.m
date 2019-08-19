%%
%Sergio Gonzalez Muriel
%Degree thesis:  Reinforcement learning for object manipulation by a robotic arm
%%
function [] = printStateFromIndex(state)
%printStateFromIndex Given a state index, prints the state 
%   Inputs:
%       state: state index
    num_elems = 12;
    dist_d = floor(state / ((num_elems^2) * (2^2)))
    ang_d = floor((mod(state, ((num_elems^2) * (2^2)))) / (num_elems * 2^2))
    alt_d = floor((mod(mod(state, ((num_elems^2) * (2^2))), (num_elems * (2^2)))) / (2^2))
    object_picked = floor((mod(mod(mod(state, ((num_elems^2) * (2^2))), (num_elems * (2^2))), (2^2))) / 2)
    folded = floor(mod(mod(mod(mod(state, ((num_elems^2) * (2^2))), (num_elems * (2^2))), (2^2)) , 2))
end


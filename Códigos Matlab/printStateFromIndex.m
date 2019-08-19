function [] = printStateFromIndex(state)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
    num_elems = 12;
    dist_d = floor(state / ((num_elems^2) * (2^2)))
    ang_d = floor((mod(state, ((num_elems^2) * (2^2)))) / (num_elems * 2^2))
    alt_d = floor((mod(mod(state, ((num_elems^2) * (2^2))), (num_elems * (2^2)))) / (2^2))
    object_picked = floor((mod(mod(mod(state, ((num_elems^2) * (2^2))), (num_elems * (2^2))), (2^2))) / 2)
    folded = floor(mod(mod(mod(mod(state, ((num_elems^2) * (2^2))), (num_elems * (2^2))), (2^2)) , 2))
end


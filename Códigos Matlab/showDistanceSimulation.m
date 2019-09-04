%%
%Sergio Gonzalez Muriel
%Degree thesis:  Reinforcement learning for object manipulation by a robotic arm
%%
function [] = showDistanceSimulation(filename, simulation)
% Shows the distances between the V's of each episode
%   Inputs:
%       filename: The name of the log without extension
%       simulation: simuation number to show
    log = strcat('iteration_distance_log_', filename, '.txt');
    fileID = fopen(log);
    distances = [];
    sim = 0;
    figure();
    while(~isempty(sim) && sim <= simulation && ~(feof(fileID)))
        C = textscan(fileID, '%d %d %f %f', 1, 'delimiter', ',');
        sim = C{1};
        if(sim == simulation)
            distances = [distances C{3}];
        end
    end
    plot(distances, '-d');
    xlabel('Step'); ylabel('Distance');
    fclose(fileID);
end
%%
%Sergio Gonzalez Muriel
%Degree thesis:  Reinforcement learning for object manipulation by a robotic arm
%%
function [] = showDistanceEpisode(filename)
% Shows the distances between the V's of each episode
%   Inputs:
%       filename: The name of the log without extension
    log = strcat('distance_log_', filename, '.txt');
    fileID = fopen(log);
    distances = [];
    figure();
    while(~(feof(fileID)))
        C = textscan(fileID, '%f %f', 1, 'delimiter', ',');
        distances = [distances C{1}];
    end
    plot(distances, '-d');
    xlabel('Episode'); ylabel('Distance');
    fclose(fileID);
end


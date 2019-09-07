%%
%Sergio Gonzalez Muriel
%Degree thesis:  Reinforcement learning for object manipulation by a robotic arm
%%
function [] = showDistanceEpisode(filename, episode)
% Shows the distances between the V's of each episode
%   Inputs:
%       filename: The name of the log without extension
%       episode: episode number to show
    log = strcat('iteration_distance_log_', filename, '.txt');
    fileID = fopen(log);
    distances = [];
    ep = 0;
    figure();
    while(~isempty(ep) && ep <= episode && ~(feof(fileID)))
        C = textscan(fileID, '%d %d %f %f', 1, 'delimiter', ',');
        ep = C{1};
        if(ep == episode)
            distances = [distances C{3}];
        end
    end
    plot(distances, '-d');
    xlabel('Step'); ylabel('Distance');
    fclose(fileID);
end
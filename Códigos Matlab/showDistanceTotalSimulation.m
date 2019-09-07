%%
%Sergio Gonzalez Muriel
%Degree thesis:  Reinforcement learning for object manipulation by a robotic arm
%%
function [] = showDistanceTotalSimulation(filename)
% Shows the distances between the V's of each step on each episode
%   Inputs:
%       filename: The name of the log without extension
    log = strcat('iteration_distance_log_', filename, '.txt');
    fileID = fopen(log);
    distances = [];
    changeOfEpisode = [];
    ep = 0;
    counter = 1;
    figure();
    while(~isempty(ep) && ~(feof(fileID)))
        C = textscan(fileID, '%d %d %f %f', 1, 'delimiter', ',');
        if(C{1} > ep)
            ep = C{1};
            changeOfEpisode = [changeOfEpisode counter];
        end
        distances = [distances C{3}];
        counter = counter + 1;
    end
    plot(distances, '-d', 'MarkerSize', 10);
    hold on;
    for i=1:size(changeOfEpisode,2)
        plot(changeOfEpisode(i), distances(changeOfEpisode(i)), 'rd', 'MarkerSize', 10);
    end
    xlabel('Step'); ylabel('Distance');
    set(gca, 'FontSize', 40);
    set(gca, 'YTick', 0:10:120);
    grid on;
    ax =  gca;
    ax.GridAlpha = 0.5;
    fclose(fileID);
end
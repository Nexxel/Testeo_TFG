%%
%Sergio Gonzalez Muriel
%Degree thesis:  Reinforcement learning for object manipulation by a robotic arm
%%
function [] = QLNumberSteps(filename)
    %Gets the number of steps of each episode and plots them
    %   filename: Simplified log file
    ep = 1; it = 0;
    fileID = fopen(filename);
    steps = [];
    while (~feof(fileID))
          C = textscan(fileID, ...
         '%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %q %f %d %f %f %d', ...
         1, 'delimiter', ',');
        if (C{1} > ep)
             ep = C{1};
             steps = [steps it];
        end
        it = C{2};
    end
    steps = [steps it];
    fclose(fileID);
    plot(steps, 'b-d');
    xlabel('Episode'); ylabel('Number of steps');
    xlim([0,130]); ylim([0,201]);
    set(gca, 'XTick', 0:10:130);
    set(gca, 'YTick', 0:20:201);
    set(gca, 'FontSize', 40);
    grid on;
    ax = gca;
    ax.GridAlpha = 0.5;
end


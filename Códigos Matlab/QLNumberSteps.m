%%
%Sergio Gonzalez Muriel
%Degree thesis:  Reinforcement learning for object manipulation by a robotic arm
%%
function [] = QLNumberSteps(filename)
    %Gets the number of steps of each simulation and plots them
    %   filename: Simplified log file
    sim = 1; it = 0;
    fileID = fopen(filename);
    steps = [];
    while (~feof(fileID))
          C = textscan(fileID, ...
         '%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %q %f %d %f %f %d', ...
         1, 'delimiter', ',');
        if (C{1} > sim)
             sim = C{1};
             steps = [steps it];
        end
        it = C{2};
    end
    steps = [steps it];
    fclose(fileID);
    plot(steps, 'b-d');
    xlabel('Simulation'); ylabel('Number of steps');
    xlim([0,130]); ylim([0,201]);
    set(gca, 'XTick', 0:5:130);
    set(gca, 'YTick', 0:10:201);
    set(gca, 'FontSize', 20);
end


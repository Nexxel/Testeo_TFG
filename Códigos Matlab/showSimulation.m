%%
%Sergio Gonzalez Muriel
%Degree thesis:  Reinforcement learning for object manipulation by a robotic arm
%%
function [outputArg1,outputArg2] = showSimulation(filename, simulation)
% Show the simulation in a figure
%   Inputs:
%       filename: The name of the log without extension
%       simulation: simuation number to show
    object_position_log = strcat('object_position_log_', filename, '.txt');
    robot_position_log = strcat('position_log_', filename, '.txt');
    fileID = fopen(object_position_log);
    sim = 0;
    while(~isempty(sim) && sim <= simulation && ~(feof(fileID)))
        C = textscan(fileID, '%d %f %f %f', 1, 'delimiter', ',');
        sim = C{1};
        if(sim == simulation)
            plot(C{2}, C{3}, 'gs');
        end
    end
    if (isempty(sim))
        quit;
    end
    hold on;
    fileID = fopen(robot_position_log);
    sim = 0; initialPos = true;
    x = []; y = [];
    while(~isempty(sim) && sim <= simulation && ~(feof(fileID)))
        C = textscan(fileID, '%d %d %f %f %f', 1, 'delimiter', ',');
        sim = C{1};
        if(sim == simulation)
            if(initialPos)
                x = [x C{3}];
                y = [y C{4}];
                initialPos = false;
            else
                x = [x C{3}];
                y = [y C{4}];
            end
        end
    end
    plot(x(1), y(1), 'rd');
    for i = 2:size(x,2)
        quiver(x(i-1), y(i-1), x(i)-x(i-1), y(i)-y(i-1), 0, 'color', 'b');
    end
    legend("Object position", "Initial position", "Robot movement");
    xlabel('X'); ylabel('Y');
    hold off;
end


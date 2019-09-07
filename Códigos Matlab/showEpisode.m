%%
%Sergio Gonzalez Muriel
%Degree thesis:  Reinforcement learning for object manipulation by a robotic arm
%%
function [] = showEpisode(filename, episode)
% Shows the episode in a figure
%   Inputs:
%       filename: The name of the log without extension
%       episode: simuation number to show
    object_position_log = strcat('object_position_log_', filename, '.txt');
    robot_position_log = strcat('position_log_', filename, '.txt');
    fileID = fopen(object_position_log);
    ep = 0;
    while(~isempty(ep) && ep <= episode && ~(feof(fileID)))
        C = textscan(fileID, '%d %f %f %f', 1, 'delimiter', ',');
        ep = C{1};
        if(ep == episode)
            figure();
            % Plot circle
            th = 0:pi/50:2*pi;
            r = (3/9 - 0.037);
            xunit = r * cos(th) + C{2};
            yunit = r * sin(th) + C{3};
            h = plot(xunit, yunit, 'r-', 'LineWidth', 3);
            hold on;
            % Plot object
            plot(C{2}, C{3}, 'r.', 'MarkerSize', 40);
        end
    end
    fclose(fileID);
    fileID = fopen(robot_position_log);
    ep = 0; initialPos = true;
    x = []; y = [];
    while(~isempty(ep) && ep <= episode && ~(feof(fileID)))
        C = textscan(fileID, '%d %d %f %f %f', 1, 'delimiter', ',');
        ep = C{1};
        if(ep == episode)
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
    plot(x,y,'b-d', 'MarkerSize', 10, 'LineWidth', 3);
    plot(x(1), y(1), 'k.', 'MarkerSize', 40);
    for i = 2:size(x,2)
        quiver(x(i-1), y(i-1), x(i)-x(i-1), y(i)-y(i-1), 0, 'color', 'b', 'LineWidth', 3);
    end
    legend("Object reachable zone","Object position", "Robot trajectory", "Initial position", 'Location', 'Best');
    xlabel('X(m)'); ylabel('Y(m)');
    xlim([-0.4, 1.10]); ylim([-0.85, 0.85])
    set(gca, 'XTick', -0.4:0.1:1.10);
    set(gca, 'YTick', -0.85:0.1:0.85);
    set(gca, 'FontSize', 30);
    grid on;
    ax = gca;
    ax.GridAlpha = 0.5;
    hold off;
    fclose(fileID);
end


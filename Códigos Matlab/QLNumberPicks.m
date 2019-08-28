%%
%Sergio Gonzalez Muriel
%Degree thesis:  Reinforcement learning for object manipulation by a robotic arm
%%
function [] = QLNumberPicks(filename)
    %Gets the number times the robot picks the object while learning and
    % prints it
    %   filename: Simplified log file
    fileID = fopen(filename);
    sim = 0;
    numberPicks = 0;
    while (~feof(fileID))
          C = textscan(fileID, ...
         '%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %q %f %d %f %f %d', ...
         1, 'delimiter', ',');
        if (C{17} > 90)
             numberPicks = numberPicks + 1;
        end
        if(~isempty(C{1}))
            sim = C{1};
        end
    end
    percentage = (double(numberPicks) / double(sim)) * 100;
    fclose(fileID);
    fprintf('The robot has picked the object %d times up to %d (%.2f%%)\n', numberPicks, sim, percentage);
end
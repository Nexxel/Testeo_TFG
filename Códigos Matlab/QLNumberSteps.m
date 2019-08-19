function [] = QLNumberSteps(filename)
    %Get the number of steps of each simulation and plot them
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
    plot(steps);
    xlabel('Simulation'); ylabel('Number of steps');
end


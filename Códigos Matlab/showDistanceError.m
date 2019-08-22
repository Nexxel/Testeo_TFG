%%
%Sergio Gonzalez Muriel
%Degree thesis:  Reinforcement learning for object manipulation by a robotic arm
%%
% Show the distance error of our implementation
log = 'distance_error_log_4m.txt';
fileID = fopen(log);
real_dist = [];
errors = [];
while(~(feof(fileID)))
    C = textscan(fileID, '%f %f', 1, 'delimiter', ',');
    if(~isempty(C{1}))
        real_dist = [real_dist C{1}];
        errors = [errors C{2}];
    end
end
fclose(fileID);
plot(real_dist, errors, 'b-');
xlabel('Real distance(m)'); ylabel('Error(m)');
grid on;
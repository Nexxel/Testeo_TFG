%%
%Sergio Gonzalez Muriel
%Degree thesis:  Reinforcement learning for object manipulation by a robotic arm
%%
% Code for plotting Policy
num_elems = 10;
pairCount = zeros(11,10,5);

for i=1:num_states
    dist_d = floor((i-1) / ((num_elems^2) * (2^2)));
    ang_d = floor((mod(i-1, ((num_elems^2) * (2^2)))) / (num_elems * 2^2));
    
    policy_tmp = Policy(i) + 1;
    
    if(V(i) > 0)
        pairCount(dist_d + 1, ang_d + 1, policy_tmp) = pairCount(dist_d + 1, ang_d + 1, policy_tmp) + 1;
    end
    
end

for i=1:5
    figure(i);
    heatmap(0:9, 0:10, pairCount(:,:,i), 'ColorMap', jet);
    title(['Action', ' ', int2str(i-1)]);
    xlabel('Angle');  
    ylabel('Distance');
    caxis([0 (max(max(max(pairCount))))])
    grid on;
    set(gca, 'FontSize', 40);
end

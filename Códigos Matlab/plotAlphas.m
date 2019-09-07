%%
%Sergio Gonzalez Muriel
%Degree thesis:  Reinforcement learning for object manipulation by a robotic arm
%%
% Code for plotting different alphas convergency
x = [1:150];
figure();
plot(x, 1./x, x, 1./(x.^0.5),x, 1./(x.^(1/3)), x, 1./(x.^0.25), 'LineWidth', 3)
legend('1/x', '1/x^{0.5}', '1/x^{0.33}', '1/x^{0.25}');
xlabel('Number of iterations');
ylabel('\alpha');
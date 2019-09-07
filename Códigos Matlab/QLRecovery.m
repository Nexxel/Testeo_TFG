%%
%Sergio Gonzalez Muriel
%Degree thesis:  Reinforcement learning for object manipulation by a robotic arm
%%
function [] = QLRecovery(filename, varargin)
%QLRECOVERY Recovers the state given a log file, a number of episode and
%a number of step in the episode
%   filename: Simplified log file
% Optional:
%   episode: Number of episode
%   step: Number of step in episode
%  discr_level: Discretization level
%  num_actions: Number of possible actions
if (nargin > 5)
    error("QLRecovery support up to 5 variables");
end

switch nargin
    case 1
        episode = 1;
        step = 1;
        discr_level = 9;
        num_actions = 5;
    case 2
        episode = varargin{1};
        step = 1;
        discr_level = 9;
        num_actions = 5;
    case 3
        episode = varargin{1};
        step = varargin{2};
        discr_level = 9;
        num_actions = 5;
    case 4
        episode = varargin{1};
        step = varargin{2};
        discr_level = varargin{3};
        num_actions = 5;
    case 5
        episode = varargin{1};
        step = varargin{2};
        discr_level = varargin{3};
        num_actions = varargin{4};        
end
 ep = 0; it = 0;
 num_states = (discr_level+2)*((discr_level+1)^2)*(2^2);
 visit_matrix = zeros(num_states,num_actions);
 q_matrix = zeros(num_states, num_actions);
 V = zeros(num_states,1);
 Policy = zeros(num_states,1);
 fileID = fopen(filename);
 while(ep < episode || (ep == episode && it < step))
      C = textscan(fileID, ...
     '%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %q %f %d %f %f %d', ...
     1, 'delimiter', ',');
    if(C{1} <= episode)
         ep = C{1};
         it = C{2};
         s = C{3};
         s_dist = C{4};
         s_ang = C{5};
         s_height = C{6};
         s_picked = C{7};
         s_folded = C{8};
         sp = C{9};
         sp_dist = C{10};
         sp_ang = C{11};
         sp_height = C{12};
         sp_picked = C{13};
         sp_folded = C{14};
         a = C{15};
         a_str = C{16}{1};
         R = C{17};
         visit_matrix((s+1), (a+1)) = C{18};
         q_matrix((s+1), (a+1)) = C{19};
         V((s+1)) = C{20};
         Policy((s+1)) = C{21};
    else
        break;
    end
 end
 fclose(fileID);
 clear filename fileID C ans episode step varargin; 
 save('QL_Recovery');
end


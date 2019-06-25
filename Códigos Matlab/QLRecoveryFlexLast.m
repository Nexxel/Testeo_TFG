function [] = QLRecoveryFlexLast(filename, varargin)
%QLRECOVERY Recover the state given a log file, a number of simulation and
%a number of step in the simulation
%   filename: Simplified log file
%   simulation: Number of simulation
%   step: Number of step in simulation
if (nargin > 5)
    error("QLRecovery support up to 5 variables");
end

switch nargin
    case 1
        simulation = 1;
        step = 1;
        discr_level = 5;
        num_actions = 5;
    case 2
        simulation = varargin{1};
        step = 1;
        discr_level = 5;
        num_actions = 5;
    case 3
        simulation = varargin{1};
        step = varargin{2};
        discr_level = 5;
        num_actions = 5;
    case 4
        simulation = varargin{1};
        step = varargin{2};
        discr_level = varargin{3};
        num_actions = 5;
    case 5
        simulation = varargin{1};
        step = varargin{2};
        discr_level = varargin{3};
        num_actions = varargin{4};        
end
 sim = 0; it = 0;
 num_states = (discr_level+2)*(discr_level+1)^2*2^2;
 visit_matrix = zeros(num_states,num_actions);
 q_matrix = zeros(num_states, num_actions);
 V = zeros(num_states,1);
 Policy = zeros(num_states,1);
 fileID = fopen(filename);
 while(sim < simulation || (sim == simulation && it < step))
      C = textscan(fileID, ...
     '%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %q %f %d %f %f %d', ...
     1, 'delimiter', ',');
    if(C{1} <= simulation)
         sim = C{1};
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
 clear filename fileID C ans simulation step varargin; 
 save('QL_Recovery');
end


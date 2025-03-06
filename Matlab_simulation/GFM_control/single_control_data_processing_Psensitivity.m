%% 02/25/24
%% dVOC load perturbation
% Updated on 02/26/24 withall Vbus phasors

% Load simulated SIMULINK data for different load perturbation durations and locations.
% All results saved in time series format in 'simout' cell.

% Author: Shaohui Liu



%% Load simulation files
% datapath =
% '/mnt/Data1/Dyn_learning/Matlab_simulation/GFM_9bus/Sim_Outputs/dVOC/'; % PMU
% datapath = '/mnt/Data1/Dyn_learning/Matlab_simulation/GFM_9bus/Sim_Outputs/dVOC_phasor/'; % phasor corrected 02/26/24
% datapath = '/mnt/Data1/Dyn_learning/Matlab_simulation/GFM_control/Sim_Outputs/dVOC_single_control/'; % with pm and Vf
datapath = '/mnt/Data1/Dyn_learning/Matlab_simulation/GFM_control/Sim_Outputs/Psensitivity/';
% datapath = '/mnt/Data1/Dyn_learning/Matlab_simulation/GFM_control/Sim_Outputs/dVOC_single_control_DC20/';

nl = 5; % location
ni = 10; % duration
nj = 10; % magnitude (control)

load_all = 1;
if load_all < 1 
    % Filename='results400_9bus_dVOC_load.mat';
    % % load(strcat(datapath,Filename));
    % load(strcat(datapath,Filename),'out_GFM3_V_terminal0')
    % load(strcat(datapath,Filename),'out_GFM3_states0')
    % Filename='bus_output_all.mat'
    % load(strcat(datapath,Filename),'t1')
else
    t0 = cell(nl*ni*nj,1);
    t1 = cell(nl*ni*nj,1);
    out_bus9_V_terminal0 = cell(nl*ni*nj,1);
    out_SM_V_terminal0 = cell(nl*ni*nj,1);
    out_SM_states0 = cell(nl*ni*nj,1);
    % out_GFM2_V_terminal0 = cell(nl*ni*nj,1);
    % out_GFM2_states0 = cell(nl*ni*nj,1);
    out_GFM3_V_terminal0 = cell(nl*ni*nj,1);
    out_GFM3_states0 = cell(nl*ni*nj,1);
    out_GFM3_control0 = cell(nl*ni*nj,1);
    out_p0 = cell(nl*ni*nj,1); 
    out_freq0 = cell(nl*ni*nj,1);
    out_v0 = cell(nl*ni*nj,1);
    % out_bus_all0 = cell(nl*ni*nj,1);

    for l = 1 : nl
    for i = 1 : ni*1
        for j = 1 : nj
            % i=10;
            % l=2;
            Filename=sprintf('Location_%d_Duration_%d_dP_%d%.mat', l, i,j);
            load(strcat(datapath,Filename));
            disp(strcat(Filename,' loaded.'))
            
            % i = 0;
            % l=1;
            t0{(l-1)*100 + (i-1)*10+j} = sim_out.out_v.Time;
            out_bus9_V_terminal0{(l-1)*100 + (i-1)*10+j} = sim_out.out_bus9_V_terminal.Data;
            out_SM_V_terminal0{(l-1)*100 + (i-1)*10+j} = sim_out.out_SM_V_terminal.Data;
            out_SM_states0{(l-1)*100 + (i-1)*10+j} = sim_out.out_SM_states.Data;
            % out_GFM2_V_terminal0{(l-1)*10 + i} = sim_out.out_GFM2_V_terminal.Data;
            % out_GFM2_states0{(l-1)*10 + i} = sim_out.out_GFM2_states.Data;
            out_GFM3_V_terminal0{(l-1)*100 + (i-1)*10+j} = sim_out.out_GFM3_V_terminal.Data;
            out_GFM3_states0{(l-1)*100 + (i-1)*10+j} = sim_out.out_GFM3_states.Data;
            out_GFM3_control0{(l-1)*100 + (i-1)*10+j} = sim_out.out_control.Data;
            out_p0{(l-1)*100 + (i-1)*10+j} = sim_out.out_p.Data;
            out_freq0{(l-1)*100 + (i-1)*10+j} = sim_out.out_freq.Data;
            out_v0{(l-1)*100 + (i-1)*10+j} = sim_out.out_v.Data;
            t1{(l-1)*100 + (i-1)*10+j} = sim_out.out_GFM3_V_terminal.Time;
            % out_bus_all0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_bus_V_phasor.Data;

            
            % {(l-1)*100 + (i-1)*10 + j} = ans.Pm.Data;
        end
    end
    end
end

% Time step is not uniform
% x

%% Test plot

% ni = 10;
% nj = 10;

t_fault = find(t0{1} > 5);

figure
for i = 1 : ni*nj*nl
plot(t0{i}(t_fault(1):end),out_freq0{i}(t_fault(1):end,1),'LineWidth',2,'DisplayName',strcat('SM',num2str(i)));
% plot(t0{i}(t_fault(1):end),out_freq0{i}(t_fault(1):end,2),'LineWidth',2,'DisplayName',strcat('GFM',num2str(i)));
hold on
end
grid on
legend()
% legend('SM','Inverter1','Inverter2')
title('Freq. deviation')









%% GFM 3 data
%% Load aggregated simulation data
% nl = 1; % location
% ni = 1; % duration
% nj = 10; % magnitude
% 
% % load(strcat(datapath,Filename),'out_GFM3_V_terminal0')
% 
% % datapath = '/mnt/Data1/Dyn_learning/Matlab_simulation/GFM_9bus/Sim_Outputs/dVOC/';
% % Filename = 'out_GFM2_part1.mat';
% % load(strcat(datapath,Filename))
% 
% out_GFM3_states00 = out_GFM2_states0;
% out_GFM3_V_terminal00 = out_GFM2_V_terminal0;
% Filename = 'out_GFM2_part2.mat';
% load(strcat(datapath,Filename));
% 
% [out_GFM3_states00{201:end}] = deal(out_GFM2_states0{201:end}); % deal matches up the input and output lists
% [out_GFM3_V_terminal00{201:end}] = deal(out_GFM2_V_terminal0{201:end});
% 
% % restore initial after combining
% out_GFM3_states0 = out_GFM3_states00;
% out_GFM3_V_terminal0 = out_GFM3_V_terminal00;


%% Convert to array (GFM)

% l=1;i=10;j=1;
% Filename=sprintf('Location_%d_Duration_%d%.mat', l, i);
%             load(strcat(datapath,Filename));
%             disp(strcat(Filename,' loaded.'))

% t2 = sim_out.out_SM_V_terminal.Time;
t2 = sim_out.out_GFM3_V_terminal.Time;
t0 = cell(1,1);
% t0{1} = sim_out.out_SM_states.Time;
t0{1} = sim_out.out_GFM3_states.Time;
n_test = nl*ni*nj;
n_step1 = size(t2,1); % PMU
% n_step = size(t0{1},1); % not uniform, pick the largest
n_step_list = zeros(n_test,1);
for i = 1 : n_test
    n_step_list(i) = size(out_GFM3_states0{i},1);
end
n_step = max(n_step_list);


% t_data = zeros(n_step,1);
freq_data = zeros(n_step,n_test);
Delta_data = zeros(n_step,n_test);
Vsd_data = zeros(n_step,n_test);
Vsq_data = zeros(n_step,n_test);
Isd_data = zeros(n_step,n_test);
Isq_data = zeros(n_step,n_test);
Vd_data = zeros(n_step,n_test);
Vq_data = zeros(n_step,n_test);
Id_data = zeros(n_step,n_test);
Iq_data = zeros(n_step,n_test);
Pe_data = zeros(n_step,n_test);
Qe_data = zeros(n_step,n_test);
controlP_data = zeros(n_step,n_test);
controlQ_data = zeros(n_step,n_test);
% virtual PMU
Vbus_data = zeros(n_step1,n_test);
Theta_date = zeros(n_step1,n_test);
% SM PMU as ref
Vbus_data_SM = zeros(n_step1,n_test);
Theta_data_SM = zeros(n_step1,n_test);
Vbus_data_bus9 = zeros(n_step1,n_test);
Theta_data_bus9 = zeros(n_step1,n_test);
% out_SM_V_terminal0


t_data = t0{1};
for i = 1 : n_test
    Pe_data(n_step-n_step_list(i)+1:end,i) = out_GFM3_states0{i}(:,15);
    Qe_data(n_step-n_step_list(i)+1:end,i) = out_GFM3_states0{i}(:,16);
    freq_data(n_step-n_step_list(i)+1:end,i) = out_GFM3_states0{i}(:,14);
    Delta_data(n_step-n_step_list(i)+1:end,i) = out_GFM3_states0{i}(:,13); % not deviation
    Vsd_data(n_step-n_step_list(i)+1:end,i) = out_GFM3_states0{i}(:,10);
    Vsq_data(n_step-n_step_list(i)+1:end,i) = out_GFM3_states0{i}(:,11);
    Isd_data(n_step-n_step_list(i)+1:end,i) = out_GFM3_states0{i}(:,7);
    Isq_data(n_step-n_step_list(i)+1:end,i) = out_GFM3_states0{i}(:,8);
    Vd_data(n_step-n_step_list(i)+1:end,i) = out_GFM3_states0{i}(:,4);
    Vq_data(n_step-n_step_list(i)+1:end,i) = out_GFM3_states0{i}(:,5);
    Id_data(n_step-n_step_list(i)+1:end,i) = out_GFM3_states0{i}(:,1);
    Iq_data(n_step-n_step_list(i)+1:end,i) = out_GFM3_states0{i}(:,2);
    controlP_data(n_step-n_step_list(i)+1:end,i) = out_GFM3_control0{i}(:,1);
    controlQ_data(n_step-n_step_list(i)+1:end,i) = out_GFM3_control0{i}(:,2);
    
    % terminal bus
    Vbus_data(:,i) = out_GFM3_V_terminal0{i}(:,3);
    Theta_date(:,i) = out_GFM3_V_terminal0{i}(:,2); % 1 is bus frequency
    Vbus_data_SM(:,i) = out_SM_V_terminal0{i}(:,3);
    Theta_data_SM(:,i) = out_SM_V_terminal0{i}(:,2);
    Vbus_data_bus9(:,i) = out_bus9_V_terminal0{i}(:,3);
    Theta_data_bus9(:,i) = out_bus9_V_terminal0{i}(:,2);
end

%% Theta discontinuity

Theta_data1 = Theta_date;
Theta_data1_SM = Theta_data_SM;
Theta_data1_bus9 = Theta_data_bus9;
for i = 1 : size(Theta_data1,2)
    % tic
    for j = 1 : size(Theta_data1,1) - 1
        % GFM
        if Theta_data1(j+1,i) - Theta_data1(j,i) > 180 % pi for phasor/radian, 180 for PMU/degree
            Theta_data1(j+1:end,i) = Theta_data1(j+1:end,i) - 2*180;%pi;
        elseif Theta_data1(j,i) - Theta_data1(j+1,i) > pi
            Theta_data1(j+1:end,i) = Theta_data1(j+1:end,i) + 2*180;%pi;
        % else  % redundant
        %     Theta_data1(j+1:end,i) = Theta_data1(j+1:end,i);
        end
        % SM
        if Theta_data1_SM(j+1,i) - Theta_data1_SM(j,i) > 180 % pi for phasor/radian, 180 for PMU/degree
            Theta_data1_SM(j+1:end,i) = Theta_data1_SM(j+1:end,i) - 2*180;%pi;
        elseif Theta_data1_SM(j,i) - Theta_data1_SM(j+1,i) > pi
            Theta_data1_SM(j+1:end,i) = Theta_data1_SM(j+1:end,i) + 2*180;%pi;
            % SM
        end
        if Theta_data1_bus9(j+1,i) - Theta_data1_bus9(j,i) > 180 % pi for phasor/radian, 180 for PMU/degree
            Theta_data1_bus9(j+1:end,i) = Theta_data1_bus9(j+1:end,i) - 2*180;%pi;
        elseif Theta_data1_bus9(j,i) - Theta_data1_bus9(j+1,i) > pi
            Theta_data1_bus9(j+1:end,i) = Theta_data1_bus9(j+1:end,i) + 2*180;%pi;
        % else  % redundant
        %     Theta_data1(j+1:end,i) = Theta_data1(j+1:end,i);
        end
    end
    % t2=toc;
    % disp(i)
end

%% plot
n_bus=1;
% Theta_data1 = Theta_date;
n_start = find(t2>5,1); % 15s
n_end = find(t2>7.9,1); 
d_rate1 = 100/4; % downsample for PMU
figure
for i = 1 : n_bus
    nexttile
    for j = 1 : n_test
        % temp = Theta_data1(n_start:n_end,i+i_test*9)-Theta_data1(n_start:n_end,1+i_test*9);
        temp = Theta_data1(n_start:n_end,j);
        plot(t2(n_start:d_rate1:n_end),temp(1:d_rate1:end),"LineWidth",2);
        hold on
    end
    % xlim([15,15.5])
    % title(strcat('Bus',num2str(i)))
    % legend
end

xx
%% downsample (GFM)
d_rate = 100;
d_rate1 = 100/4; % for PMU

t_data = t_data(1 : d_rate:end,:);
freq_data = freq_data(1 : d_rate:end,:);
Delta_data = Delta_data(1 : d_rate:end,:);
Vd_data = Vd_data(1 : d_rate:end,:);
Vq_data = Vq_data(1 : d_rate:end,:);
Id_data = Id_data(1 : d_rate:end,:);
Iq_data = Iq_data(1 : d_rate:end,:);
Vsd_data = Vsd_data(1 : d_rate:end,:);
Vsq_data = Vsq_data(1 : d_rate:end,:);
Isd_data = Isd_data(1 : d_rate:end,:);
Isq_data = Isq_data(1 : d_rate:end,:);
Pe_data = Pe_data(1 : d_rate:end,:);
Qe_data = Qe_data(1 : d_rate:end,:);
controlP_data = controlP_data(1 : d_rate:end,:);
controlQ_data = controlQ_data(1 : d_rate:end,:);

Vbus_data = Vbus_data(1 : d_rate1:end,:);
Theta_date = Theta_data1(1 : d_rate1:end,:);

xx

%% save to csv (GFM)
filename0 = 'bus20_control_GFM_';

filename = strcat(filename0,'vbus.csv');
writematrix(Vbus_data,filename)
filename = strcat(filename0,'theta.csv');
writematrix(Theta_date,filename)

filename = strcat(filename0,'Pcontrol.csv');
writematrix(controlP_data,filename)
filename = strcat(filename0,'Qcontrol.csv');
writematrix(controlQ_data,filename)

filename = strcat(filename0,'time.csv');
writematrix(t_data,filename)

filename = strcat(filename0,'Pe_data.csv');
writematrix(Pe_data,filename)
filename = strcat(filename0,'Qe_data.csv');
writematrix(Qe_data,filename)

filename = strcat(filename0,'freq_data.csv');
writematrix(freq_data,filename)


filename = strcat(filename0,'delta_data.csv');
writematrix(Delta_data,filename)


filename = strcat(filename0,'vd.csv');
writematrix(Vd_data,filename)

filename = strcat(filename0,'vq.csv');
writematrix(Vq_data,filename)

filename = strcat(filename0,'id.csv');
writematrix(Id_data,filename)

filename = strcat(filename0,'iq.csv');
writematrix(Iq_data,filename)

filename = strcat(filename0,'vsd.csv');
writematrix(Vsd_data,filename)

filename = strcat(filename0,'vsq.csv');
writematrix(Vsq_data,filename)

filename = strcat(filename0,'isd.csv');
writematrix(Isd_data,filename)

filename = strcat(filename0,'isq.csv');
writematrix(Isq_data,filename)
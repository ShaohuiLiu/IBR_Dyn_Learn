%% 11/07/23

% Load simulated SIMULINK data for different load perturbation durations and locations.
% All results saved in time series format in 'simout' cell.

% Author: Shaohui Liu



%% Load simulation files
datapath = '/mnt/Data1/Dyn_learning/Matlab_simulation/GFM_9bus/Sim_Outputs/';

nl = 4; % location
ni = 10; % duration
nj = 10; % magnitude

load_all = 0;
if load_all < 1 
    Filename='results400_9bus.mat';
    % load(strcat(datapath,Filename));
    load(strcat(datapath,Filename),'out_GFM3_V_terminal0')
    load(strcat(datapath,Filename),'out_GFM3_states0')
    % load(strcat(datapath,Filename),'t0')
else
    t0 = cell(nl*ni*nj,1);
    out_SM_V_terminal0 = cell(nl*ni*nj,1);
    out_SM_states0 = cell(nl*ni*nj,1);
    out_GFM2_V_terminal0 = cell(nl*ni*nj,1);
    out_GFM2_states0 = cell(nl*ni*nj,1);
    out_GFM3_V_terminal0 = cell(nl*ni*nj,1);
    out_GFM3_states0 = cell(nl*ni*nj,1);
    out_p0 = cell(nl*ni*nj,1); 
    out_freq0 = cell(nl*ni*nj,1);
    out_v0 = cell(nl*ni*nj,1);

    for l = 1 : nl
    for i = 1 : ni
        for j = 1 : nj
            Filename=sprintf('Location_%d_Duration_%d_Magnitude_%d%.mat', l, i, j);
            load(strcat(datapath,Filename));
            disp(strcat(Filename,' loaded.'))
            
            t0{(l-1)*100 + (l-1)*100 + (i-1)*10 + j} = sim_out.out_v.Time;
            out_SM_V_terminal0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_SM_V_terminal.Data;
            out_SM_states0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_SM_states.Data;
            out_GFM2_V_terminal0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_GFM2_V_terminal.Data;
            out_GFM2_states0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_GFM2_states.Data;
            out_GFM3_V_terminal0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_GFM3_V_terminal.Data;
            out_GFM3_states0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_GFM3_states.Data;
            out_p0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_p.Data;
            out_freq0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_freq.Data;
            out_v0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_v.Data;
            
            % {(l-1)*100 + (i-1)*10 + j} = ans.Pm.Data;
        end
    end
    end
end

% Time step is not uniform


%% Test plot

ni = 10;
nj = 10;

t_fault = find(t0{1} > 15);

figure
for i = 1 : ni*nj
plot(t0{i}(t_fault(1):end),out_freq0{i}(t_fault(1):end,:),'LineWidth',2);
hold on
end
grid on
% legend('SM','Inverter1','Inverter2')
title('Freq. deviation')


%% Convert to array (SM)

l=1;i=1;j=1;
Filename=sprintf('Location_%d_Duration_%d_Magnitude_%d%.mat', l, i, j);
            load(strcat(datapath,Filename));
            disp(strcat(Filename,' loaded.'))

t2 = sim_out.out_SM_V_terminal.Time;

n_test = nl*ni*nj;
n_step = size(t0{1},1);

n_step1 = size(t2,1); % PMU

% t_data = zeros(n_step,1);
freq_data = zeros(n_step,n_test);
% dw_data = zeros(n_step,n_test);
Vd_data = zeros(n_step,n_test);
Vq_data = zeros(n_step,n_test);
Vbus_data = zeros(n_step1,n_test);
Theta_date = zeros(n_step1,n_test);
Delta_data = zeros(n_step,n_test);

t_data = t0{1};
for i = 1 : n_test
    freq_data(:,i) = out_SM_states0{i}(:,1);
    Vd_data(:,i) = out_SM_states0{i}(:,3);
    Vq_data(:,i) = out_SM_states0{i}(:,4);
    Vbus_data(:,i) = out_SM_V_terminal0{i}(:,3);
    Theta_date(:,i) = out_SM_V_terminal0{i}(:,2); % 1 is bus frequency
    Delta_data(:,i) = out_SM_states0{i}(:,2);
end

%% downsample (SM)
d_rate = 100;
d_rate1 = 100/4; % for PMU

t_data = t_data(1 : d_rate:end,:);
freq_data = freq_data(1 : d_rate:end,:);
Vd_data = Vd_data(1 : d_rate:end,:);
Vq_data = Vq_data(1 : d_rate:end,:);
Vbus_data = Vbus_data(1 : d_rate1:end,:);
Theta_date = Theta_date(1 : d_rate1:end,:);
Delta_data = Delta_data(1 : d_rate:end,:);

%% save to csv (SM)
filename0 = 'ieee9bus400_';

filename = strcat(filename0,'vbus.csv');
writematrix(Vbus_data,filename)
filename = strcat(filename0,'theta.csv');
writematrix(Theta_date,filename)

filename = strcat(filename0,'time.csv');
writematrix(t_data,filename)


filename = strcat(filename0,'freq_data.csv');
writematrix(freq_data,filename)


filename = strcat(filename0,'delta_data.csv');
writematrix(Delta_data,filename)


filename = strcat(filename0,'vd.csv');
writematrix(Vd_data,filename)

filename = strcat(filename0,'vq.csv');
writematrix(Vq_data,filename)



%% Convert to array (GFM)

l=1;i=1;j=1;
Filename=sprintf('Location_%d_Duration_%d_Magnitude_%d%.mat', l, i, j);
            load(strcat(datapath,Filename));
            disp(strcat(Filename,' loaded.'))

t2 = sim_out.out_SM_V_terminal.Time;
t0 = cell(1,1);
t0{1} = sim_out.out_SM_states.Time;
n_test = nl*ni*nj;
n_step = size(t0{1},1);

n_step1 = size(t2,1); % PMU

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
Vbus_data = zeros(n_step1,n_test);
Theta_date = zeros(n_step1,n_test);


t_data = t0{1};
for i = 1 : n_test
    freq_data(:,i) = out_GFM3_states0{i}(:,14);
    Delta_data(:,i) = out_GFM3_states0{i}(:,13); % not deviation
    Vsd_data(:,i) = out_GFM3_states0{i}(:,10);
    Vsq_data(:,i) = out_GFM3_states0{i}(:,11);
    Isd_data(:,i) = out_GFM3_states0{i}(:,7);
    Isq_data(:,i) = out_GFM3_states0{i}(:,8);
    Vd_data(:,i) = out_GFM3_states0{i}(:,4);
    Vq_data(:,i) = out_GFM3_states0{i}(:,5);
    Id_data(:,i) = out_GFM3_states0{i}(:,1);
    Iq_data(:,i) = out_GFM3_states0{i}(:,2);
    
    % terminal bus
    Vbus_data(:,i) = out_GFM3_V_terminal0{i}(:,3);
    Theta_date(:,i) = out_GFM3_V_terminal0{i}(:,2); % 1 is bus frequency
end

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

Vbus_data = Vbus_data(1 : d_rate1:end,:);
Theta_date = Theta_date(1 : d_rate1:end,:);

%% save to csv (GFM)
filename0 = 'ieee9bus400_GFM3_';

filename = strcat(filename0,'vbus.csv');
writematrix(Vbus_data,filename)
filename = strcat(filename0,'theta.csv');
writematrix(Theta_date,filename)

filename = strcat(filename0,'time.csv');
writematrix(t_data,filename)


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
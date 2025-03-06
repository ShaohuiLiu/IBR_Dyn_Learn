%% 10/09/23

% Load simulated SIMULINK data for different fault durations and locations.
% All results saved in time series format in 'ans'.

% Author: Shaohui Liu



%% Load simulation files
datapath = '../mnt/Data1/Dyn_learning/Matlab_simulation/400_Outputs/'; % 400

ni = 20;
nj = 20;

load_all = 1;
if load_all < 1 
    Filename='results400.mat';
    load(strcat(datapath,Filename));
else
    t0 = cell(ni,nj);
    Pm0 = cell(ni,nj);
    Vf0 = cell(ni,nj);
    freq0 = cell(ni,nj);
    dw0 = cell(ni,nj);
    Vd0 = cell(ni,nj);
    Vq0 = cell(ni,nj);
    Pe0 = cell(ni,nj); 
    Qe0 = cell(ni,nj);
    Vbus0 = cell(ni,nj);
    Theta0 = cell(ni,nj);
    Ibus0 = cell(ni,nj);
    ThetaI0 = cell(ni,nj);
    Delta0 = cell(ni,nj);
    dDelta0 = cell(ni,nj);
    
    for i = 1 : ni
        for j = 1 : nj
            Filename=sprintf('400_outputs/Duration_%d_Location_%d%.mat', i, j);
            % load(strcat(datapath,Filename,'.mat'));
            load(Filename);
            disp(strcat(Filename, ' loaded.'))
            
            t0{i,j} = sim_out.Pm.Time;
            Pm0{i,j} = sim_out.Pm.Data;
            Vf0{i,j} = sim_out.Vf.Data;
            freq0{i,j} = sim_out.wm.Data;
            dw0{i,j} = sim_out.dw.Data;
            Vd0{i,j} = sim_out.Vd.Data;
            Vq0{i,j} = sim_out.Vq.Data;
            Pe0{i,j} = sim_out.Peo.Data;
            Qe0{i,j} = sim_out.Qeo.Data;
            Vbus0{i,j} = sim_out.V_terminal.Data(:,1); % balanced, take 1 phase
            Theta0{i,j} = sim_out.V_terminal.Data(:,4);
            Ibus0{i,j} = sim_out.current.Data(:,1); % balanced, take 1 phase
            ThetaI0{i,j} = sim_out.current.Data(:,4);
            Delta0{i,j} = sim_out.delta.Data;
            dDelta0{i,j} = sim_out.ddelta.Data;
            % {i,j} = ans.Pm.Data;
        end
    end
end

% Time step is not uniform

%%
figure
nexttile
plot(sim_out.Vf.Time,sim_out.Vf.Data)
title('Vf')
nexttile
plot(sim_out.Pm.Time,sim_out.Pm.Data)
title('Pm')
nexttile
plot(sim_out.V_terminal.Time,sim_out.V_terminal.Data(:,1))
title('|V|')
nexttile
plot(sim_out.V_terminal.Time,sim_out.V_terminal.Data(:,4))
title('Theta')

%% Test plot

ni = 20;
nj = 20;

t_fault = find(t0{1} > 15);

figure
for i = 1 : ni
    for j = 1 : nj
plot(t0{i,j}(t_fault(1):end),dw0{i,j}(t_fault(1):end),'LineWidth',2);
hold on
    end
end
grid on
% legend('SM','Inverter1','Inverter2')
title('Freq. deviation')


%% Convert to array

n_test = ni*nj;
n_step = size(t0{1},1);

% t_data = zeros(n_step,1);
Pm_data = zeros(n_step,n_test);
Vf_data = zeros(n_step,n_test);
freq_data = zeros(n_step,n_test);
dw_data = zeros(n_step,n_test);
Vd_data = zeros(n_step,n_test);
Vq_data = zeros(n_step,n_test);
Pe_data = zeros(n_step,n_test); 
Qe_data = zeros(n_step,n_test);
Vbus_data = zeros(n_step,n_test);
Theta_date = zeros(n_step,n_test);
I_data = zeros(n_step,n_test);
ThetaI_data = zeros(n_step,n_test);
Delta_data = zeros(n_step,n_test);
dDelta_data = zeros(n_step,n_test);

t_data = t0{1};
for i = 1 : ni
    for j = 1 : nj
    Pm_data(:,(i-1)*20+j) = Pm0{i,j};
    Vf_data(:,(i-1)*20+j) = Vf0{i,j};
    freq_data(:,(i-1)*20+j) = freq0{i,j};
    dw_data(:,(i-1)*20+j) = dw0{i,j};
    Vd_data(:,(i-1)*20+j) = Vd0{i,j};
    Vq_data(:,(i-1)*20+j) = Vq0{i,j};
    Pe_data(:,(i-1)*20+j) = Pe0{i,j}; 
    Qe_data(:,(i-1)*20+j) = Qe0{i,j};
    Vbus_data(:,(i-1)*20+j) = Vbus0{i,j};
    Theta_date(:,(i-1)*20+j) = Theta0{i,j};
    I_data(:,(i-1)*20+j) = Ibus0{i,j};
    ThetaI_data(:,(i-1)*20+j) = ThetaI0{i,j};
    Delta_data(:,(i-1)*20+j) = Delta0{i,j};
    dDelta_data(:,(i-1)*20+j) = dDelta0{i,j};
    end
end

%% downsample
d_rate = 100;

t_data = t_data(1 : d_rate:end,:);
Pm_data = Pm_data(1 : d_rate:end,:);
Vf_data = Vf_data(1 : d_rate:end,:);
freq_data = freq_data(1 : d_rate:end,:);
dw_data = dw_data(1 : d_rate:end,:);
Vd_data = Vd_data(1 : d_rate:end,:);
Vq_data = Vq_data(1 : d_rate:end,:);
Pe_data = Pe_data(1 : d_rate:end,:); 
Qe_data = Qe_data(1 : d_rate:end,:);
Vbus_data = Vbus_data(1 : d_rate:end,:);
Theta_date = Theta_date(1 : d_rate:end,:);
I_data = I_data(1 : d_rate:end,:);
ThetaI_data = ThetaI_data(1 : d_rate:end,:);
Delta_data = Delta_data(1 : d_rate:end,:);
dDelta_data = dDelta_data(1 : d_rate:end,:);

%% save to csv
filename0 = 'SMIB400_new_';

filename = strcat(filename0,'vbus.csv');
writematrix(Vbus_data,filename)
filename = strcat(filename0,'theta.csv');
writematrix(Theta_date,filename)
filename = strcat(filename0,'current.csv');
writematrix(I_data,filename)
filename = strcat(filename0,'thetai.csv');
writematrix(ThetaI_data,filename)

filename = strcat(filename0,'time.csv');
writematrix(t_data,filename)

filename = strcat(filename0,'input_pm.csv');
writematrix(Pm_data,filename)


filename = strcat(filename0,'input_vf.csv');
writematrix(Vf_data,filename)

filename = strcat(filename0,'freq_data.csv');
writematrix(freq_data,filename)

filename = strcat(filename0,'domega.csv');
writematrix(dw_data,filename)

filename = strcat(filename0,'delta_data.csv');
writematrix(Delta_data,filename)

filename = strcat(filename0,'ddelta.csv');
writematrix(dDelta_data,filename)

filename = strcat(filename0,'vd.csv');
writematrix(Vd_data,filename)

filename = strcat(filename0,'vq.csv');
writematrix(Vq_data,filename)

filename = strcat(filename0,'pe.csv');
writematrix(Pe_data,filename)

filename = strcat(filename0,'qe.csv');
writematrix(Qe_data,filename)





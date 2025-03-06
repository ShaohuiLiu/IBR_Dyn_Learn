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
datapath = '/mnt/Data1/Dyn_learning/Matlab_simulation/GFM_9bus/Sim_Outputs/dVOC_phasor_input/'; % with pm and Vf

nl = 4; % location
ni = 10; % duration
nj = 10; % magnitude

load_all = 1;
if load_all < 1 
    Filename='results400_9bus_dVOC_load.mat';
    % load(strcat(datapath,Filename));
    load(strcat(datapath,Filename),'out_GFM3_V_terminal0')
    load(strcat(datapath,Filename),'out_GFM3_states0')
    % Filename='bus_output_all.mat'
    % load(strcat(datapath,Filename),'t1')
else
    t0 = cell(nl*ni*nj,1);
    t1 = cell(nl*ni*nj,1);
    out_SM_V_terminal0 = cell(nl*ni*nj,1);
    out_SM_states0 = cell(nl*ni*nj,1);
    out_GFM2_V_terminal0 = cell(nl*ni*nj,1);
    out_GFM2_states0 = cell(nl*ni*nj,1);
    out_GFM3_V_terminal0 = cell(nl*ni*nj,1);
    out_GFM3_states0 = cell(nl*ni*nj,1);
    % out_p0 = cell(nl*ni*nj,1); 
    % out_freq0 = cell(nl*ni*nj,1);
    % out_v0 = cell(nl*ni*nj,1);
    % out_bus_all0 = cell(nl*ni*nj,1);

    for l = 1 : nl
    for i = 1 : ni
        for j = 1 : nj
            Filename=sprintf('Location_%d_Duration_%d_Magnitude_%d%.mat', l, i, j);
            load(strcat(datapath,Filename));
            disp(strcat(Filename,' loaded.'))
            
            t0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_v.Time;
            out_SM_V_terminal0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_SM_V_terminal.Data;
            out_SM_states0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_SM_states.Data;
            % out_GFM2_V_terminal0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_GFM2_V_terminal.Data;
            % out_GFM2_states0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_GFM2_states.Data;
            % out_GFM3_V_terminal0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_GFM3_V_terminal.Data;
            % out_GFM3_states0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_GFM3_states.Data;
            % out_p0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_p.Data;
            % out_freq0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_freq.Data;
            % out_v0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_v.Data;
            t1{(l-1)*100 + (i-1)*10 + j} = sim_out.out_bus_V_phasor.Time;
            % out_bus_all0{(l-1)*100 + (i-1)*10 + j} = sim_out.out_bus_V_phasor.Data;
            
            % {(l-1)*100 + (i-1)*10 + j} = ans.Pm.Data;
        end
    end
    end
end

% Time step is not uniform
x

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

%% SM data
%% Load aggregated simulation data
nl = 4; % location
ni = 10; % duration
nj = 10; % magnitude

% load(strcat(datapath,Filename),'out_GFM3_V_terminal0')

% datapath = '/mnt/Data1/Dyn_learning/Matlab_simulation/GFM_9bus/Sim_Outputs/dVOC/';
datapath = '/mnt/Data1/Dyn_learning/Matlab_simulation/GFM_9bus/Sim_Outputs/dVOC_phasor_input/';
% Filename = 'out_SM_part1.mat';
Filename = 'out_SM_all.mat';
load(strcat(datapath,Filename))

% out_SM_states00 = out_SM_states0;
% out_SM_V_terminal00 = out_SM_V_terminal0;
% % Filename = 'out_SM_part2.mat';
% % load(strcat(datapath,Filename));
% 
% % [out_SM_states00{201:end}] = deal(out_SM_states0{201:end}); % deal matches up the input and output lists
% % [out_SM_V_terminal00{201:end}] = deal(out_SM_V_terminal0{201:end});
% 
% % restore initial after combining
% out_SM_states0 = out_SM_states00;
% out_SM_V_terminal0 = out_SM_V_terminal00;


%% Convert to array (SM)

l=1;i=1;j=1;
Filename=sprintf('Location_%d_Duration_%d_Magnitude_%d%.mat', l, i, j);
            load(strcat(datapath,Filename));
            disp(strcat(Filename,' loaded.'))

t2 = sim_out.out_SM_V_terminal.Time;
t0 = cell(1,1);
t0{1} = sim_out.out_SM_states.Time;

n_test = nl*ni*nj;
n_step = size(t0{1},1);

n_step_list = zeros(n_test,1);
for i = 1 : n_test
    n_step_list(i) = size(out_SM_states0{i},1);
end
n_step2 = max(n_step_list);
% temp = find(n_step>=n_step1);
% t2 = t1{temp};

n_step1 = size(t2,1); % PMU

% t_data = zeros(n_step,1);
freq_data = zeros(n_step2,n_test);
% dw_data = zeros(n_step,n_test);
Vd_data = zeros(n_step2,n_test);
Vq_data = zeros(n_step2,n_test);
Vbus_data = zeros(n_step1,n_test);
Theta_date = zeros(n_step1,n_test);
Delta_data = zeros(n_step2,n_test);
Pm_data = zeros(n_step2,n_test);
Vref_data = zeros(n_step2,n_test);

Pe_data = zeros(n_step2,n_test);
Qe_data = zeros(n_step2,n_test);

t_data = t0{1};
for i = 1 : n_test
    freq_data(n_step2 - n_step_list(i)+1:end,i) = out_SM_states0{i}(:,1);
    Vd_data(n_step2 - n_step_list(i)+1:end,i) = out_SM_states0{i}(:,3);
    Vq_data(n_step2 - n_step_list(i)+1:end,i) = out_SM_states0{i}(:,4);
    Vbus_data(:,i) = out_SM_V_terminal0{i}(:,3);
    Theta_date(:,i) = out_SM_V_terminal0{i}(:,2); % 1 is bus frequency
    Delta_data(n_step2 - n_step_list(i)+1:end,i) = out_SM_states0{i}(:,2);
    % control input
    Pm_data(n_step2 - n_step_list(i)+1:end,i) = out_SM_states0{i}(:,5);
    Vref_data(n_step2 - n_step_list(i)+1:end,i) = out_SM_states0{i}(:,6);
    % power
    Pe_data(n_step2 - n_step_list(i)+1:end,i) = out_SM_states0{i}(:,7);
    Qe_data(n_step2 - n_step_list(i)+1:end,i) = out_SM_states0{i}(:,8);

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
Pm_data = Pm_data(1 : d_rate:end,:);
Vref_data = Vref_data(1 : d_rate:end,:);
Qe_data = Qe_data(1 : d_rate:end,:);
Pe_data = Pe_data(1 : d_rate:end,:);

%% save to csv (SM)
filename0 = 'ieee9bus400_dVOC_SM_';

filename = strcat(datapath,filename0,'vbus_0714.csv');
writematrix(Vbus_data,filename)
filename = strcat(datapath,filename0,'theta_0714.csv');
writematrix(Theta_date,filename)

filename = strcat(datapath,filename0,'time_0714.csv');
writematrix(t_data,filename)


filename = strcat(datapath,filename0,'freq_data_0714.csv');
writematrix(freq_data,filename)


filename = strcat(datapath,filename0,'delta_data_0714.csv');
writematrix(Delta_data,filename)


filename = strcat(datapath,filename0,'vd_0714.csv');
writematrix(Vd_data,filename)

filename = strcat(datapath,filename0,'vq_0714.csv');
writematrix(Vq_data,filename)

filename = strcat(datapath,filename0,'pm_0714.csv');
writematrix(Pm_data,filename)

filename = strcat(datapath,filename0,'vref_0714.csv');
writematrix(Vref_data,filename)

filename = strcat(datapath,filename0,'pe_0714.csv');
writematrix(Pe_data,filename)

filename = strcat(datapath,filename0,'qe_0714.csv');
writematrix(Qe_data,filename)


%% Bus phasor 9 buses (phasor 02/28/24)
%% Network coupling (all Vbus)
nl = 4; % location
ni = 10; % duration
nj = 10; % magnitude

% datapath = '/mnt/Data1/Dyn_learning/Matlab_simulation/GFM_9bus/Sim_Outputs/dVOC/';
datapath = '/mnt/Data1/Dyn_learning/Matlab_simulation/GFM_9bus/Sim_Outputs/dVOC_phasor_input/';
Filename = 'out_bus_all.mat';
% Filename = 'bus_output_all.mat';
load(strcat(datapath,Filename)) % out_bus_all0, t1

t2 = t1{1};
n_test = nl*ni*nj;
n_step1 = size(t2,1); % PMU

% %%
% figure
% i=100;
% for j = 1 : 9
%     plot(t2,out_bus_all0{i}(:,2*(j-1)+2))
%     hold on
% end
% 
% figure
% i=100;
% for j = 1 : 9 % downsample
%     plot(t2(1 : d_rate1:end),out_bus_all0{i}(1 : d_rate1:end,2*(j-1)+2))
%     hold on
% end

% %%
% figure
% i=100;
% for j = 1 : 9
%     plot(downsample(t2,100),downsample(out_bus_all0{i}(:,2*(j-1)+2),100))
%     hold on
% end



%%

n_step = zeros(n_test,1);
for i = 1 : n_test
    n_step(i) = size(out_bus_all0{i},1);
end
n_step1 = max(n_step);
temp = find(n_step>=n_step1);
t2 = t1{temp};

Vbus_data = zeros(n_step1,n_test*9);
Theta_data = zeros(n_step1,n_test*9);

for i = 1:n_test
    temp_v = zeros(n_step1,9);
    temp_theta = zeros(n_step1,9);
    for j = 1 : 9
        temp_v(n_step1-n_step(i)+1:end,j) = out_bus_all0{i}(:,3*(j-1)+1);
        temp_theta(n_step1-n_step(i)+1:end,j) = out_bus_all0{i}(:,3*(j-1)+2);
    end
    Vbus_data(:,9*(i-1)+1:9*i) = temp_v;
    Theta_data(:,9*(i-1)+1:9*i) = temp_theta;
end

%%
% figure
% for j = 1 : 9
%     nexttile
%     plot(out_bus_V_phasor.Time,out_bus_V_phasor.Data(:,3*(j-1)+2))
%     xlim([14.95,16])
% end


%% fix discontinuity of theta

Theta_data1 = Theta_data;
for i = 1 : size(Theta_data1,2)
    % tic
    for j = 1 : size(Theta_data1,1) - 1
        if Theta_data1(j+1,i) - Theta_data1(j,i) > 180 % pi for phasor/radian, 180 for PMU/degree
            Theta_data1(j+1:end,i) = Theta_data1(j+1:end,i) - 2*180;%pi;
        elseif Theta_data1(j,i) - Theta_data1(j+1,i) > pi
            Theta_data1(j+1:end,i) = Theta_data1(j+1:end,i) + 2*180;%pi;
        % else  % redundant
        %     Theta_data1(j+1:end,i) = Theta_data1(j+1:end,i);
        end
    end
    % t2=toc;
    % disp(i)
end

% Theta_data = Theta_data1;

d_rate1 = 100/4; % downsample for states, /4 if PMU

Vbus_data2 = Vbus_data(1 : d_rate1:end,:);
Theta_data2 = Theta_data1(1 : d_rate1:end,:);

t_data = t2(1 : d_rate1:end,:);

%%

filename0 = 'ieee9bus400_dVOC_AllBus_';

filename = strcat(datapath,filename0,'vbus.csv');
writematrix(Vbus_data2,filename)
filename = strcat(datapath,filename0,'theta.csv');
writematrix(Theta_data2,filename)

filename = strcat(datapath,filename0,'time.csv');
writematrix(t_data,filename)

%% relative angle
Theta_data2 = zeros(size(Theta_data1));
ref_bus = 9;
for i_test = 1 : n_test
    for i = 1 : n_bus
            % if i == 2 || i == 9
            %     Theta_data2(:,i+(i_test-1)*9) = Theta_data1(:,i+(i_test-1)*9)+Theta_data1(:,1+(i_test-1)*9);
            % else
            %     Theta_data2(:,i+(i_test-1)*9) = Theta_data1(:,i+(i_test-1)*9)-Theta_data1(:,1+(i_test-1)*9);
            % end
            Theta_data2(:,i+(i_test-1)*9) = Theta_data1(:,i+(i_test-1)*9)-Theta_data1(:,ref_bus+(i_test-1)*9);
    end
end

Theta_data2 = Theta_data2(1 : d_rate1:end,:);
filename = strcat(filename0,'theta_dev9.csv');
writematrix(Theta_data2,filename)


%% Check raw theta after fix discontinuity
n_bus = 9;

il = 1; it = 1; im = 1; % loc, duration, mag
i_test = (il-1)*100 + (it-1)*10 + im;

n_start = find(t2>15,1); % 15s
n_end = find(t2>17,1); 

figure
for i = 1 : n_bus
    nexttile
    % deviation
    % plot(t2(n_start:n_end),Theta_data1(n_start:n_end,i+i_test*9)-Theta_data1(n_start,i+i_test*9),"DisplayName",strcat('Bus',num2str(i)),"LineWidth",2);
    % relative angle
    % if i == 2 || i == 9
    %     temp = Theta_data1(n_start:n_end,i+i_test*9)+Theta_data1(n_start:n_end,1+i_test*9);
    %     plot(t2(n_start:d_rate1:n_end),temp(1:d_rate1:end),"DisplayName",strcat('Bus',num2str(i)),"LineWidth",2);
    % else
    for j = 1 : n_test
        % temp = Theta_data1(n_start:n_end,i+i_test*9)-Theta_data1(n_start:n_end,1+i_test*9);
        temp = Theta_data1(n_start:n_end,i+(j-1)*9)-Theta_data1(n_start:n_end,1+(j-1)*9);
        plot(t2(n_start:d_rate1:n_end),temp(1:d_rate1:end),"DisplayName",strcat('Bus',num2str(i)),"LineWidth",2);
        hold on
    end
    % xlim([15,15.5])
    title(strcat('Bus',num2str(i)))
    % legend
end
test_name = strcat('Test-Loc',num2str(il),'Dur',num2str(it),'Mag',num2str(im));
sgtitle(strcat('d\theta:',test_name))

%% |v|

n_start = find(t_data>15,1); % 15s
n_end = find(t_data>17,1); 

figure
for i = 1 : n_bus
    nexttile
    for j = 1 : n_test
        % temp = Theta_data1(n_start:n_end,i+i_test*9)-Theta_data1(n_start:n_end,1+i_test*9);
        temp = Vbus_data2(n_start:n_end,i+(j-1)*9)-Vbus_data2(n_start,i+(j-1)*9);
        plot(t_data(n_start:n_end),temp(1:end),"DisplayName",strcat('Bus',num2str(i)),"LineWidth",2);
        hold on
    end
    % xlim([15,15.5])
    title(strcat('Bus',num2str(i)))
    % legend
end
test_name = strcat('Test-Loc',num2str(il),'Dur',num2str(it),'Mag',num2str(im));
sgtitle(strcat('|v|:',test_name))


%% Verify V phasor plot
n_bus = 9;

il = 4; it = 1; im = 1; % loc, duration, mag
i_test = (il-1)*100 + (it-1)*10 + im;

n_start = 1921; % 15s

figure
nexttile
for i = 1 : n_bus
    plot(t_data,Vbus_data(:,i+i_test*9)-Vbus_data(n_start,i+i_test*9),"DisplayName",strcat('Bus',num2str(i)),"LineWidth",2);
    hold on
end
xlim([15,18])
title('d|v|:')
legend
nexttile
for i = 1 : n_bus
    plot(t_data(n_start:end),Theta_data(n_start:end,i+i_test*9)-Theta_data(n_start,i+i_test*9),"DisplayName",strcat('Bus',num2str(i)),"LineWidth",2);
    hold on
end
xlim([15,18])
title('d\theta')
legend
test_name = strcat('Test-Loc',num2str(il),'Dur',num2str(it),'Mag',num2str(im));
sgtitle(test_name)
hold off

% %%
figure
for i = 1 : n_bus
    nexttile
    plot(t_data,Vbus_data(:,i+i_test*9)-Vbus_data(n_start,i+i_test*9),"DisplayName",strcat('Bus',num2str(i)),"LineWidth",2);
    xlim([15,18])
    legend
end
sgtitle(strcat('d|v|:',test_name))
%%
figure
for i = 1 : n_bus
    nexttile
    plot(t_data,Theta_data(:,i+i_test*9)-Theta_data(n_start,i+i_test*9),"DisplayName",strcat('Bus',num2str(i)),"LineWidth",2);
    xlim([15,15.5])
    legend
end
sgtitle(strcat('d\theta:',test_name))

%% Check relative angle
n_bus = 9;
il = 4; it = 1; im = 1; % loc, duration, mag
i_test = (il-1)*100 + (it-1)*10 + im;

n_start = 1921; % 15s

figure
ref_bus = 1;
theta_ref = Theta_data(:,ref_bus+i_test*9)-Theta_data(n_start,ref_bus+i_test*9);
nexttile
for i = 1 : n_bus
    plot(t_data,Theta_data(:,i+i_test*9)-theta_ref,"DisplayName",strcat('Bus',num2str(i)),"LineWidth",2);
    hold on
end
xlim([15,18])
legend
title('Relative angle')
nexttile
for i = 1 : n_bus
    temp = Theta_data(:,i+i_test*9)-theta_ref;
    plot(t_data,temp-temp(1),"DisplayName",strcat('Bus',num2str(i)),"LineWidth",2);
    hold on
end
xlim([15,18])
legend
title('Deviation of relative angle')
test_name = strcat('Test-Loc',num2str(il),'Dur',num2str(it),'Mag',num2str(im));
sgtitle(strcat('\theta:',test_name))





%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 




%% Bus phasor 9 buses (PMU)
%% Network coupling (PMU all Vbus)
nl = 4; % location
ni = 10; % duration
nj = 10; % magnitude

datapath = '/mnt/Data1/Dyn_learning/Matlab_simulation/GFM_9bus/Sim_Outputs/dVOC/';
Filename = 'out_bus_all.mat';
load(strcat(datapath,Filename)) % out_bus_all0, t1

t2 = t1{1};
n_test = nl*ni*nj;
n_step1 = size(t2,1); % PMU

%%

Vbus_data = zeros(n_step1,n_test*9);
Theta_data = zeros(n_step1,n_test*9);

for i = 1:n_test
    temp_v = zeros(n_step1,9);
    temp_theta = zeros(n_step1,9);
    for j = 1 : 9
        temp_v(:,j) = out_bus_all0{i}(:,3*(j-1)+3);
        temp_theta(:,j) = out_bus_all0{i}(:,3*(j-1)+2);
    end
    Vbus_data(:,9*(i-1)+1:9*i) = temp_v;
    Theta_data(:,9*(i-1)+1:9*i) = temp_theta;
end

d_rate1 = 100/4; % downsample for PMU

Vbus_data = Vbus_data(1 : d_rate1:end,:);
Theta_data = Theta_data(1 : d_rate1:end,:);

t_data = t2(1 : d_rate1:end,:);

% %%

filename0 = 'ieee9bus400_dVOC_AllBus_';

% filename = strcat(filename0,'vbus.csv');
% writematrix(Vbus_data,filename)
% filename = strcat(filename0,'theta.csv');
% writematrix(Theta_data,filename)
% 
% filename = strcat(filename0,'time.csv');
% writematrix(t_data,filename)

%% Verify V phasor plot
n_bus = 9;

il = 4; it = 1; im = 1; % loc, duration, mag
i_test = (il-1)*100 + (it-1)*10 + im;

n_start = 1921; % 15s

figure
nexttile
for i = 1 : n_bus
    plot(t_data,Vbus_data(:,i+i_test*9)-Vbus_data(n_start,i+i_test*9),"DisplayName",strcat('Bus',num2str(i)),"LineWidth",2);
    hold on
end
xlim([15,18])
title('d|v|:')
legend
nexttile
for i = 1 : n_bus
    plot(t_data,Theta_data(:,i+i_test*9)-Theta_data(n_start,i+i_test*9),"DisplayName",strcat('Bus',num2str(i)),"LineWidth",2);
    hold on
end
xlim([15,18])
title('d\theta')
legend
test_name = strcat('Test-Loc',num2str(il),'Dur',num2str(it),'Mag',num2str(im));
sgtitle(test_name)
hold off

% %%
figure
for i = 1 : n_bus
    nexttile
    plot(t_data,Vbus_data(:,i+i_test*9)-Vbus_data(n_start,i+i_test*9),"DisplayName",strcat('Bus',num2str(i)),"LineWidth",2);
    xlim([15,18])
    legend
end
sgtitle(strcat('d|v|:',test_name))

figure
for i = 1 : n_bus
    nexttile
    plot(t_data,Theta_data(:,i+i_test*9)-Theta_data(n_start,i+i_test*9),"DisplayName",strcat('Bus',num2str(i)),"LineWidth",2);
    xlim([15,18])
    legend
end
sgtitle(strcat('d\theta:',test_name))

%% Check relative angle
n_bus = 9;
il = 4; it = 1; im = 1; % loc, duration, mag
i_test = (il-1)*100 + (it-1)*10 + im;

n_start = 1921; % 15s

figure
ref_bus = 1;
theta_ref = Theta_data(:,ref_bus+i_test*9)-Theta_data(n_start,ref_bus+i_test*9);
nexttile
for i = 1 : n_bus
    plot(t_data,Theta_data(:,i+i_test*9)-theta_ref,"DisplayName",strcat('Bus',num2str(i)),"LineWidth",2);
    hold on
end
xlim([15,18])
legend
title('Relative angle')
nexttile
for i = 1 : n_bus
    temp = Theta_data(:,i+i_test*9)-theta_ref;
    plot(t_data,temp-temp(1),"DisplayName",strcat('Bus',num2str(i)),"LineWidth",2);
    hold on
end
xlim([15,18])
legend
title('Deviation of relative angle')
test_name = strcat('Test-Loc',num2str(il),'Dur',num2str(it),'Mag',num2str(im));
sgtitle(strcat('\theta:',test_name))



%% GFM 3 data
%% Load aggregated simulation data
nl = 4; % location
ni = 10; % duration
nj = 10; % magnitude

% load(strcat(datapath,Filename),'out_GFM3_V_terminal0')

datapath = '/mnt/Data1/Dyn_learning/Matlab_simulation/GFM_9bus/Sim_Outputs/dVOC/';
Filename = 'out_GFM2_part1.mat';
load(strcat(datapath,Filename))

out_GFM3_states00 = out_GFM2_states0;
out_GFM3_V_terminal00 = out_GFM2_V_terminal0;
Filename = 'out_GFM2_part2.mat';
load(strcat(datapath,Filename));

[out_GFM3_states00{201:end}] = deal(out_GFM2_states0{201:end}); % deal matches up the input and output lists
[out_GFM3_V_terminal00{201:end}] = deal(out_GFM2_V_terminal0{201:end});

% restore initial after combining
out_GFM3_states0 = out_GFM3_states00;
out_GFM3_V_terminal0 = out_GFM3_V_terminal00;


%% Convert to array (GFM)

l=1;i=10;j=1;
Filename=sprintf('Location_%d_Duration_%d_Magnitude_%d%.mat', l, i, j);
            load(strcat(datapath,Filename));
            disp(strcat(Filename,' loaded.'))

t2 = sim_out.out_SM_V_terminal.Time;
t2 = sim_out.out_GFM3_V_terminal.Time;
t0 = cell(1,1);
t0{1} = sim_out.out_SM_states.Time;
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
Qe_date = zeros(n_step,n_test);
% virtual PMU
Vbus_data = zeros(n_step1,n_test);
Theta_date = zeros(n_step1,n_test);


t_data = t0{1};
for i = 1 : n_test
    Pe_data(n_step-n_step_list(i)+1:end,i) = out_GFM3_states0{i}(:,15);
    Qe_date(n_step-n_step_list(i)+1:end,i) = out_GFM3_states0{i}(:,16);
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
Pe_data = Pe_data(1 : d_rate:end,:);
Qe_date = Qe_date(1 : d_rate:end,:);

Vbus_data = Vbus_data(1 : d_rate1:end,:);
Theta_date = Theta_date(1 : d_rate1:end,:);

%% save to csv (GFM)
filename0 = 'ieee9bus400_dVOC_GFM2_';

filename = strcat(filename0,'vbus.csv');
writematrix(Vbus_data,filename)
filename = strcat(filename0,'theta.csv');
writematrix(Theta_date,filename)

filename = strcat(filename0,'time.csv');
writematrix(t_data,filename)

filename = strcat(filename0,'Pe_data.csv');
writematrix(Pe_data,filename)
filename = strcat(filename0,'Qe_data.csv');
writematrix(Qe_date,filename)

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
% Raw data pre-processed as variables and not down-sampled
% Date: 05/03/2024
% Author: Shaohui Liu



% Earlier is truncate then smooth, now try smooth then truncate to smoother
% the initial steps of the post-fault

%% params for tests, load original data (will be overridden by smoothing)
% Faults starts at 5s, simulations end at 8s
% Fault periods contain a lot of undesired nonlinearities

% load GFM_control20_050124.mat

n_period = ni; % 100
t_post = 2.5; % [s] after fault as data period
t_disturbance = 5+linspace(0.01,0.2,n_period); % starting from 5s


%% smoothing

K_w = find(t_data-t_data(1) >= .1,1); % smoothing window for 10Hz, later 20Hz
for i = 1 : n_test
    freq_data(:,i) = movmean(freq_data(:,i),K_w);
    % freq_data_smo1(:,i) = lowpass(freq_data0(:,i),fpass,Fs);
    Delta_data(:,i) = movmean(Delta_data(:,i),K_w);
    Vd_data(:,i) = movmean(Vd_data(:,i),K_w);
    Vq_data(:,i) = movmean(Vq_data(:,i),K_w);
    Pe_data(:,i) = movmean(Pe_data(:,i),K_w);
    Qe_data(:,i) = movmean(Qe_data(:,i),K_w);
    % controlP_data(:,i) = movmean(controlP_data(:,i),K_w);
    % controlQ_data(:,i) = movmean(controlQ_data(:,i),K_w);

    % Vd_data_smo1(:,i) = lowpass(Vd_data0(:,i),fpass,Fs);
    % Vq_data_smo1(:,i) = lowpass(Vq_data0(:,i),fpass,Fs);
    % Pe_data_smo1(:,i) = lowpass(Pe_data0(:,i),fpass,Fs);
    % Qe_data_smo1(:,i) = lowpass(Qe_data0(:,i),fpass,Fs);

    % Vbus_data0(:,i) = Vbus_data(t_end_idx_bus(i,1)-shift_n:t_end_idx_bus(i,1)+min_step_bus-1-shift_n,i);
    % Theta_data0(:,i) = theta_temp(t_end_idx_bus(i,1)-shift_n:t_end_idx_bus(i,1)+min_step_bus-1-shift_n);
end


%% Remove fault period


t_end_idx = zeros(n_test,2); % faults end
data_end_idx = zeros(n_test,2); % data end
for i = 1 : n_test
    temp_idx = mod(i,n_period);
    if temp_idx >= 1
        temp_t = t_disturbance(temp_idx);
    else
        temp_t = t_disturbance(end); % last
    end
    t_end_idx(i,1) = find(t_data>temp_t,1)+35; % 1st time step after fault, compensate PMU diff
    t_end_idx(i,2) = t_data(t_end_idx(i,1)); % time of fault ends
    % data durations
    temp_t1 = t_end_idx(i,2) + t_post;
    data_end_idx(i,1) = find(t_data>temp_t1,1)+35; % 1st time step after fault
    data_end_idx(i,2) = t_data(data_end_idx(i,1));
end
temp = data_end_idx(:,1) - t_end_idx(:,1);
min_step = min(temp);

% truncate data 
t_data0 = zeros(min_step,n_test);
freq_data0 = zeros(min_step,n_test);
Delta_data0 = zeros(min_step,n_test);
Vd_data0 = zeros(min_step,n_test);
Vq_data0 = zeros(min_step,n_test);
% Id_data0 = zeros(min_step,n_test);
% Iq_data0 = zeros(min_step,n_test);
% Vsd_data0 = zeros(min_step,n_test);
% Vsq_data0 = zeros(min_step,n_test);
% Isd_data0 = zeros(min_step,n_test);
% Isq_data0 = zeros(min_step,n_test);
Pe_data0 = zeros(min_step,n_test);
Qe_data0 = zeros(min_step,n_test);
controlP_data0 = zeros(min_step,n_test);
controlQ_data0 = zeros(min_step,n_test);

shift_n = 0;
for i = 1 : n_test
    t_data0(:,i) = t_data(t_end_idx(i,1):t_end_idx(i,1)+min_step-1);
    freq_data0(:,i) = freq_data(t_end_idx(i,1):t_end_idx(i,1)+min_step-1,i);
    Delta_data0(:,i) = Delta_data(t_end_idx(i,1):t_end_idx(i,1)+min_step-1,i);
    Vd_data0(:,i) = Vd_data(t_end_idx(i,1):t_end_idx(i,1)+min_step-1,i);
    Vq_data0(:,i) = Vq_data(t_end_idx(i,1):t_end_idx(i,1)+min_step-1,i);
    % Id_data0(:,i) = Id_data(t_end_idx(i,1):t_end_idx(i,1)+min_step-1,i);
    % Iq_data0(:,i) = Iq_data(t_end_idx(i,1):t_end_idx(i,1)+min_step-1,i);
    % Vsd_data0(:,i) = Vsd_data(t_end_idx(i,1):t_end_idx(i,1)+min_step-1,i);
    % Vsq_data0(:,i) = Vsq_data(t_end_idx(i,1):t_end_idx(i,1)+min_step-1,i);
    % Isd_data0(:,i) = Isd_data(t_end_idx(i,1):t_end_idx(i,1)+min_step-1,i);
    % Isq_data0(:,i) = Isq_data(t_end_idx(i,1):t_end_idx(i,1)+min_step-1,i);
    Pe_data0(:,i) = Pe_data(t_end_idx(i,1):t_end_idx(i,1)+min_step-1,i);
    Qe_data0(:,i) = Qe_data(t_end_idx(i,1):t_end_idx(i,1)+min_step-1,i);
    controlP_data0(:,i) = controlP_data(t_end_idx(i,1)-shift_n:t_end_idx(i,1)+min_step-1-shift_n,i);
    controlQ_data0(:,i) = controlQ_data(t_end_idx(i,1)-shift_n:t_end_idx(i,1)+min_step-1-shift_n,i);
end
t_data1 = t_data0(:,end); % just 2.5s


% %% Truncate terminal bus after fault

t_end_idx_bus = zeros(n_test,2); % faults end
data_end_idx_bus = zeros(n_test,2); % data end
for i = 1 : n_test
    temp_idx = mod(i,n_period);
    if temp_idx >= 1
        temp_t = t_disturbance(temp_idx);
    else
        temp_t = t_disturbance(end); % last
    end
    t_end_idx_bus(i,1) = find(t2>temp_t,1); % 1st time step after fault, compensate PMU diff
    t_end_idx_bus(i,2) = t2(t_end_idx_bus(i,1)); % time of fault ends
    % data durations
    temp_t1 = t_end_idx_bus(i,2) + t_post;
    data_end_idx_bus(i,1) = find(t2>temp_t1,1); % 1st time step after fault
    data_end_idx_bus(i,2) = t2(data_end_idx_bus(i,1));
end

temp_bus = data_end_idx_bus(:,1) - t_end_idx_bus(:,1);
min_step_bus = min(temp_bus);

% truncate data 
% t20 = zeros(min_step_bus,1);
Vbus_data0 = zeros(min_step_bus,n_test);
Theta_data0 = zeros(min_step_bus,n_test);

shift_n = 0;
t20 = t2(t_end_idx_bus(i,1)-shift_n:t_end_idx_bus(i,1)+min_step_bus-1-shift_n);
for i = 1 : n_test
    Vbus_data0(:,i) = Vbus_data(t_end_idx_bus(i,1)-shift_n:t_end_idx_bus(i,1)+min_step_bus-1-shift_n,i);
    theta_temp = Theta_data1(:,i)-Theta_data1_bus9(:,i); % relative to bus9, same side v.s. fault
    Theta_data0(:,i) = theta_temp(t_end_idx_bus(i,1)-shift_n:t_end_idx_bus(i,1)+min_step_bus-1-shift_n);
    % Theta_data0(:,i) =
    % Theta_date(t_end_idx_bus(i,1)-shift_n:t_end_idx_bus(i,1)+min_step_bus-1-shift_n,i); % raw angle data
end




% %% Check truncated data

figure
nexttile
for i = 1 : n_test
    plot(t_data1-t_data1(1),freq_data0(:,i),'LineWidth',1,'DisplayName',num2str(i))
    hold on
end
% legend('NumColumns',2)
title('frequency')
nexttile
for i = 1 : n_test
    plot(t_data1-t_data1(1),Delta_data0(:,i),'LineWidth',1,'DisplayName',num2str(i))
    hold on
end
% legend('NumColumns',2)
title('Angle')
nexttile
for i = 1 : n_test
    plot(t_data1-t_data1(1),Vd_data0(:,i),'LineWidth',1,'DisplayName',num2str(i))
    hold on
end
% legend('NumColumns',2)
title('Vd')
nexttile
for i = 1 : n_test
    plot(t_data1-t_data1(1),Vq_data0(:,i),'DisplayName',num2str(i))
    hold on
end
% legend('NumColumns',2)
title('Vq')
nexttile
for i = 1 : n_test
    plot(t_data1-t_data1(1),Pe_data0(:,i),'DisplayName',num2str(i))
    hold on
end
% legend('NumColumns',2)
title('Pe')
nexttile
for i = 1 : n_test
    plot(t_data1-t_data1(1),Qe_data0(:,i),'DisplayName',num2str(i))
    hold on
end
% legend('NumColumns',2)
title('Qe')
nexttile
for i = 1 : n_test
    plot(t_data1-t_data1(1),controlP_data0(:,i),'DisplayName',num2str(i))
    hold on
end
% legend('NumColumns',2)
title('Pc')
nexttile
for i = 1 : n_test
    plot(t_data1-t_data1(1),controlQ_data0(:,i),'DisplayName',num2str(i))
    hold on
end
% legend('NumColumns',2)
title('Qc')
nexttile
for i = 1 : n_test
    plot(t20-t20(1),Vbus_data0(:,i),'DisplayName',num2str(i))
    hold on
end
% legend('NumColumns',2)
title('Vbus')
nexttile
for i = 1 : n_test
    plot(t20-t20(1),Theta_data0(:,i),'DisplayName',num2str(i))
    hold on
end
% legend('NumColumns',2)
title('Theta')


%% Smoothing by moving avg.

% init.
freq_data_smo = zeros(min_step,n_test);
Delta_data_smo = zeros(min_step,n_test);
Vd_data_smo = zeros(min_step,n_test);
Vq_data_smo = zeros(min_step,n_test);
Pe_data_smo = zeros(min_step,n_test);
Qe_data_smo = zeros(min_step,n_test);
controlP_data_smo = zeros(min_step,n_test);
controlQ_data_smo = zeros(min_step,n_test);

% freq_data_smo1 = zeros(min_step,n_test); % for lowpass
% Vd_data_smo1 = zeros(min_step,n_test);
% Vq_data_smo1 = zeros(min_step,n_test);
% Pe_data_smo1 = zeros(min_step,n_test);
% Qe_data_smo1 = zeros(min_step,n_test);

% no need for V phasor for now
% Vbus_data_smo = zeros(min_step_bus,n_test);
% Theta_data_smo = zeros(min_step_bus,n_test);

% T_s=3.125e-4/4; % step
% Fs = round(1/(T_s));
% fpass = 9;

K_w = find(t_data1-t_data1(1) >= .05,1); % smoothing window for 20Hz
for i = 1 : n_test
    freq_data_smo(:,i) = movmean(freq_data0(:,i),K_w);
    % freq_data_smo1(:,i) = lowpass(freq_data0(:,i),fpass,Fs);
    Delta_data_smo(:,i) = movmean(Delta_data0(:,i),K_w);
    Vd_data_smo(:,i) = movmean(Vd_data0(:,i),K_w);
    Vq_data_smo(:,i) = movmean(Vq_data0(:,i),K_w);
    Pe_data_smo(:,i) = movmean(Pe_data0(:,i),K_w);
    Qe_data_smo(:,i) = movmean(Qe_data0(:,i),K_w);
    controlP_data_smo(:,i) = controlP_data0(:,i);
    controlQ_data_smo(:,i) = controlQ_data0(:,i);
    % controlP_data_smo(:,i) = movmean(controlP_data0(:,i),K_w);
    % controlQ_data_smo(:,i) = movmean(controlQ_data0(:,i),K_w);

    % Vd_data_smo1(:,i) = lowpass(Vd_data0(:,i),fpass,Fs);
    % Vq_data_smo1(:,i) = lowpass(Vq_data0(:,i),fpass,Fs);
    % Pe_data_smo1(:,i) = lowpass(Pe_data0(:,i),fpass,Fs);
    % Qe_data_smo1(:,i) = lowpass(Qe_data0(:,i),fpass,Fs);

    % Vbus_data0(:,i) = Vbus_data(t_end_idx_bus(i,1)-shift_n:t_end_idx_bus(i,1)+min_step_bus-1-shift_n,i);
    % Theta_data0(:,i) = theta_temp(t_end_idx_bus(i,1)-shift_n:t_end_idx_bus(i,1)+min_step_bus-1-shift_n);
end

% %%
figure
nexttile
for i = 1 : n_test
    plot(t_data1-t_data1(1),freq_data_smo(:,i),'LineWidth',1,'DisplayName',num2str(i))
    hold on
end
% legend('NumColumns',2)
title('frequency')
nexttile
for i = 1 : n_test
    plot(t_data1-t_data1(1),Delta_data_smo(:,i),'LineWidth',1,'DisplayName',num2str(i))
    hold on
end
% legend('NumColumns',2)
title('Angle')
nexttile
for i = 1 : n_test
    plot(t_data1-t_data1(1),Vd_data_smo(:,i),'LineWidth',1,'DisplayName',num2str(i))
    hold on
    % plot(t_data1-t_data1(1),Vd_data_smo1(:,i),'LineWidth',1.5,'DisplayName',strcat(num2str(i),'low'))
    % hold on
end
% legend('NumColumns',2)
title('Vd')
nexttile
for i = 1 : n_test
    plot(t_data1-t_data1(1),Vq_data_smo(:,i),'DisplayName',num2str(i))
    hold on
    % plot(t_data1-t_data1(1),Vq_data_smo1(:,i),'LineWidth',1.5,'DisplayName',strcat(num2str(i),'low'))
    % hold on
end
% legend('NumColumns',2)
title('Vq')
nexttile
for i = 1 : n_test
    plot(t_data1-t_data1(1),Pe_data_smo(:,i),'DisplayName',num2str(i))
    hold on
    % plot(t_data1-t_data1(1),Pe_data_smo1(:,i),'LineWidth',1.5,'DisplayName',strcat(num2str(i),'low'))
    % hold on
end
% legend('NumColumns',2)
title('Pe')
nexttile
for i = 1 : n_test
    plot(t_data1-t_data1(1),Qe_data_smo(:,i),'DisplayName',num2str(i))
    hold on
    % plot(t_data1-t_data1(1),Qe_data_smo1(:,i),'LineWidth',1.5,'DisplayName',strcat(num2str(i),'low'))
    % hold on
end
% legend('NumColumns',2)
title('Qe')
nexttile
for i = 1 : n_test
    plot(t_data1-t_data1(1),controlP_data_smo(:,i),'DisplayName',num2str(i))
    hold on
end
% legend('NumColumns',2)
title('Pc')
nexttile
for i = 1 : n_test
    plot(t_data1-t_data1(1),controlQ_data_smo(:,i),'DisplayName',num2str(i))
    hold on
end
% legend('NumColumns',2)
title('Qc')


% figure
% for i = 8 : 10
%     nexttile
%     plot(t_data1-t_data1(1),freq_data0(:,i),'LineWidth',1,'DisplayName',num2str(i))
%     hold on
%     plot(t_data1-t_data1(1),freq_data_smo(:,i),'LineWidth',1,'DisplayName',strcat(num2str(i),'s'))
%     % hold on
%     % plot(t_data1-t_data1(1),freq_data_smo1(:,i),'LineWidth',1,'DisplayName',strcat(num2str(i),'low'))
%     legend('NumColumns',2)
% end
% title('frequency')



%% break point
xx


%% downsample (GFM)
d_rate = 100;
d_rate1 = 100/4; % for PMU

t_temp = t_data1-t_data1(1);
t_data = t_temp(1 : d_rate:end,:);
freq_data = freq_data_smo(1 : d_rate:end,:);
Delta_data = Delta_data_smo(1 : d_rate:end,:);
Vd_data = Vd_data_smo(1 : d_rate:end,:);
Vq_data = Vq_data_smo(1 : d_rate:end,:);
Pe_data = Pe_data_smo(1 : d_rate:end,:);
Qe_data = Qe_data_smo(1 : d_rate:end,:);
controlP_data = controlP_data_smo(1 : d_rate:end,:);
controlQ_data = controlQ_data_smo(1 : d_rate:end,:);

Vbus_data = Vbus_data0(1 : d_rate1:end,:);
Theta_date = Theta_data0(1 : d_rate1:end,:);

%% save to csv (GFM)
filename0 = 'bus200_control_GFM_';

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
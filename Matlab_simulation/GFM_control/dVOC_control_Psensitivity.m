%% dVOC_control_demo.slx Data

% edited on 04/06/2024, add states collections, step change, virtual PMUs

%% Solver sample time
T_s=3.125e-4/4; % PMU sampling rate
Tend=8; % Shaohui: break at 27.69s for droop(no I limit)
T_loss= Tend; % loss of SM
T_load=[5 5]; % load disturbance, will be changed in simulation
T_en=T_load(1)-0.5;%Enabling the DC source saturation after the initial synchronization
% T_ms=0.001;
T_ms=T_s*4;
% Network base values
S_b=100*(10^6);
V_b=230*(10^3);%L-L rms voltage
f_b=50;w_b=2*pi*f_b;
P_b=S_b;Q_b=S_b;
I_b=S_b/(sqrt(3)*V_b);
Z_b=(V_b^2)/S_b;L_b=Z_b/w_b;C_b=1/(w_b*Z_b);

% Branch parameters 
R_lines=[0,0.017,0.039,0,0.0119,0.0085,0,0.032,0.01]*Z_b;
L_lines=[0.0576,0.092,0.17,0.0586,0.1008,0.072,0.0625,0.161,0.085]*L_b;
% R_14=R_lines(1); L_14=L_lines(1);
R_45=R_lines(2); L_45=L_lines(2);
% R_56=R_lines(3); L_56=L_lines(3);
% R_36=R_lines(4); L_36=L_lines(4);
% R_67=R_lines(5); L_67=L_lines(5);
R_78=R_lines(6); L_78=L_lines(6);
% R_82=R_lines(7); L_82=L_lines(7);
R_89=R_lines(8); L_89=L_lines(8);
R_94=R_lines(9); L_94=L_lines(9);

% Shunt parameters ([pu]*base)
C_4=0.1670*C_b;C_8=0.2275*C_b;%C_6=0.2835*C_b;

% Converter params
V1_rms=1000; %Low voltage side
I_b_LV=S_b/(sqrt(3)*V1_rms);
V_m=sqrt(2/3)*V1_rms;
Vdc_n=3*V_m;
n=200;
C_dc=0.008*(n);
R_f=0.001/n;
L_f=(1/n)*200*10^-6;
C_f=n*300*10^-6;
R_dc=(Vdc_n/(0.05*(S_b)/Vdc_n));
w_f=2*pi*5;


% LV/MV transformer parameters
m=100;
S_bt=S_b;
V2_rms=13800;%Medium voltage side
R1_pu=1*0.00734/m;
L1_pu=1*0.0186/m;
R2_pu=R1_pu;
L2_pu=L1_pu;
Rm_pu=10*347.82/m;
Lm_pu=10*156.68/m;

% Control parameters

%DC source and governor-turbine time constants
tau_dc=0.05;tau_g=5;
%defining SM governer gain----------------------
droop_percentage=1;
% grid-forming converter control----------------
I_b_dc=S_b/Vdc_n;
i_loss_dc=Vdc_n/R_dc;
i_ul=1.15*(S_b/Vdc_n)+i_loss_dc;%dc source saturation limits
i_ll=-1.15*(S_b/Vdc_n)-i_loss_dc;%dc source saturation limits
% DC voltage control--------------------------------
eta_1= w_b/Vdc_n;
m_p=(2*pi*0.5)/(S_b);
k_dc=eta_1/(Vdc_n*m_p);
K_p=(1/Vdc_n);
K_r=1/R_dc;
% AC voltage control--------------------------------
ki_v_ac=2*0.25;
kp_v_ac=0.001;
% Voltage loop----------------------------------------
n=200;
Kp_v =0.52;
Ki_v =(n)*1.161022;
Kff_v = 1;
Ti_v = Kp_v/Ki_v; 
% Current loop
Kp_i =0.738891;
Ki_i =(1/n)*1.19;
Kff_i = 1;
Ti_i = Kp_i / Ki_i;

%dVOC gain
m_p=(2*pi*0.5)/(S_b);
eta =  m_p*V_m^2; %compute eta from m_p
alpha = 1e-1*V_m^2;

% Network loading and set-points
base=2.25; % base load
load_change=0.75;% load disturbance
ps=base/3; %set-ponit in [MW]
qs=[0;0];
pl=S_b*ps; %loads in [W]
load_step=S_b*load_change; %disturbance in [W]

% xx

%% Run simulation
% sim('droop_model')

% Initialize disturbance level and duration
dt_load = T_s .* ones(2,1); % T_s  = 1e-4[s] is the step size
% mag_load = 1e-6 .* ones(2,1);
t_disturbance = linspace(0.01,0.2,10);
mag_disturbance = linspace(0.1,2,10);

P_delta = linspace(0,1.8,50);

for i_loc = 4 : 5
    for i_t = 10 : 10
        for i_p = 10 : 10
        dt_load(i_loc) = t_disturbance(i_t);
        % for i_mag = 10 : 10
            % mag_load(i_loc) = mag_disturbance(i_mag);
            dp = P_delta((i_loc-1)*10+i_p);
            fprintf('Disturbance loc %d, duration %.4f [s], DeltaP %.2f [pu] .\n ',i_loc,dt_load(i_loc),dp);
         
            T_load1=[T_load(1)-dt_load(1), T_load(1)]; % load disturbance duration (load5)
            % if dt_load(1) >= (T_s * 5)
            %     load_change1= 0.9 .* mag_load(1);
            % else
            %     load_change1= 1e-6; 
            % end
            % load_step1=S_b*load_change1; % disturbance [W]
            
            T_load2=[T_load(1)-dt_load(2), T_load(1)]; % load disturbance duration (load_SM) 
            % if dt_load(2) >= (T_s * 5)
            %     load_change2= 0.9 .* mag_load(2);
            % else
            %     load_change2= 1e-6; 
            % end
            % load_step2=S_b*load_change2; % disturbance [W]

            xx
            

            % Time domain simulation
            tic
            % sim('dVOC_monitor_network_gen'); % with pm and Vref
            % sim('dVOC_control_demo'); % with pm and Vref
            % sim('dVOC_control_demo_fault_2023b');
            % sim('dVOC_control_demo_fault_2023b_constDC');
            % sim('dVOC_control_demo_fault_2023b_Psensitivity');
            sim('dVOC_control_demo_fault_2023b_Psensitivity_0531');
            toc
            
            sim_out = struct;
            sim_out.out_SM_V_terminal = out_SM_V_terminal;
            sim_out.out_bus9_V_terminal = out_bus9_V_terminal;
            sim_out.out_SM_states = out_SM_states;
            % sim_out.out_GFM2_V_terminal = out_GFM2_V_terminal;
            % sim_out.out_GFM2_states = out_GFM2_states;
            sim_out.out_GFM3_V_terminal = out_GFM3_V_terminal;
            sim_out.out_GFM3_states = out_GFM3_states;
            sim_out.out_p = out_p;
            sim_out.out_q = out_q;
            sim_out.out_freq = out_freq;
            sim_out.out_v = out_v;
            sim_out.out_control = out_control;
            % sim_out.out_bus_V_phasor = out_bus_V_phasor;



            % Process data
            % Filename=sprintf('Sim_Outputs/Psensitivity/Location_%d_Duration_%d_dP_%d%.mat', i_loc, max(i_t,10),i_p); % 10 tests
            Filename=sprintf('Sim_Outputs/Psensitivity/Location_%d_Duration_%d_dP_%d%.mat', i_loc, i_t,i_p);
            disp(Filename)
            save(Filename,'sim_out')

            % restore perturbation params
            % dt_load = T_s .* ones(4,1); 
            mag_load = 1e-6 .* ones(4,1);
        % end
        dt_load = T_s .* ones(4,1); 
        end
    end
end



% fname = sprintf('droop.mat');
%save(fname)
% clc



%% Plot for droop w/ current limiter

% data
t0 = out_freq.Time;
freq0 = out_freq.Data;
% p0 = out_p.Data;
% v0 = out_v.Data;
% SM_states = out_SM_states.Data; % dw, ddelta, vd,vq

% SM states
t1 = out_SM_states.Time;
SM_states = out_SM_states.Data; % dw, ddelta, vd,vq
figure
subplot(4,1,1)
plot(t1,SM_states(:,1),'LineWidth',2,'DisplayName','\omega_{SM}');
legend
xlim([5 8])
subplot(4,1,2)
plot(t1,SM_states(:,2),'LineWidth',2,'DisplayName','\delta_{SM}');
legend
xlim([5 8])
subplot(4,1,3)
plot(t1,SM_states(:,3),'LineWidth',2,'DisplayName','Vd_{SM}');
legend
xlim([5 8])
subplot(4,1,4)
plot(t1,SM_states(:,4),'LineWidth',2,'DisplayName','Vq_{SM}');
legend
xlim([5 8])
sgtitle('Generator (SM) states')

%% SM network
% t2 = out_SM_V_terminal.Time;
% V_sm_terminal = out_SM_V_terminal.Data;
% figure
% for i = 1 : 2
% nexttile
% plot(t2,V_sm_terminal(:,i),'LineWidth',2);
% hold on
% end



%%

% frequency
figure
for i = 1 : 2
plot(t0,freq0(:,i),'LineWidth',2);
hold on
end
xlim([5 8])
grid on
legend('SM','Inverter')
title('Frequency')


% power output
p0 = out_p.Data;

figure
for i = 1 : 2
plot(t0,p0(:,i),'LineWidth',2);
hold on
end
xlim([5 8])
grid on
legend('SM','Inverter')
title('Power (P)')


% voltage
v0 = out_v.Data;

figure
for i = 1 : 2
plot(t0,v0(:,i),'LineWidth',2);
hold on
end
xlim([5 8])
grid on
legend('SM','Inverter')
title('Voltage')
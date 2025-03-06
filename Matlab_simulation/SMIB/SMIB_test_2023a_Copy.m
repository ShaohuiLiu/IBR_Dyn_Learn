%Code to run with varying fault durations and fault locations

%To change fault duration, change the end of the step
fault_end =  linspace((15+.5/60),(15+10/60),20);

%To change fault location, change the length of the transmission line
%before and after the fault
Front_line_length =  linspace(5,95,20);
End_line_length =  linspace(95,5,20);

%Make a folder to save the outputs in 
mkdir 400_outputs;

%Load the model so we can set parameters
mdl = 'SMIB_test_SL_2023a_Copy';
load_system(mdl);

path = [mdl,'/Clear'];
get_param(path,'dialogparameters')
get_param(path,'Time')

path = [mdl,'/Three-Phase PI Section Line'];
get_param(path,'dialogparameters')
get_param(path,'Length')

for i = 1:length(fault_end)
    for j = 1:length(Front_line_length)

        fprintf('Fault %d length %d .\n',i,j)
        %Fault duration saved in steps
        Fault_duration = (fault_end(i)) - 15;
        %Fault location saved at percentage into the 100 km transmission line it is
        Fault_location = Front_line_length(j);

        path = [mdl,'/Clear'];
        set_param(path,'Time',num2str(fault_end(i)));

        path = [mdl,'/Three-Phase PI Section Line'];
        set_param(path,'Length',num2str(Front_line_length(j)));

        path = [mdl,'/Three-Phase PI Section Line1'];
        set_param(path,'Length',num2str(End_line_length(j)));

        sim_out = sim('SMIB_test_SL_2023a_Copy.slx');
        Filename=sprintf('400_outputs/Duration_%d_Location_%d%.mat', i, j);
        save(Filename,'sim_out')

    end
end
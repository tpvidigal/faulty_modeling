fexp = fopen('/media/vidigal/Dados/Git/tcctpv/pid/tb/tb_Actuator/output.txt','r');
fout = fopen('/media/vidigal/Dados/Git/tcctpv/pid/tb/tb_Actuator/result.txt','r');

ml_exp = cell2mat(textscan(fexp, '%f'));
sc_out = cell2mat(textscan(fout, '%f'));
t = 1:1001;

figure
plot(t,ml_exp,'r', t,sc_out,'b.')
title('Actuator Comparsion')
xlabel('samples (0.1s)')
ylabel('gain to PID')
legend('Matlab','SystemC')

fclose(fexp);
fclose(fout);
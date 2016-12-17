fexp = fopen('/media/vidigal/Dados/Git/tcctpv/pid/tb/tb_System_Matlab/output.txt','r');
fout = fopen('/media/vidigal/Dados/Git/tcctpv/pid/tb/tb_System_Matlab/result.txt','r');

ml_exp = cell2mat(textscan(fexp, '%f'));
sc_out = cell2mat(textscan(fout, '%f'));
t = 1:1001;

figure
plot(t,ml_exp,'r', t,sc_out,'b.')
title('System Comparsion')
xlabel('samples (0.1s)')
ylabel('output of the System')
legend('Matlab','SystemC')

fclose(fexp);
fclose(fout);
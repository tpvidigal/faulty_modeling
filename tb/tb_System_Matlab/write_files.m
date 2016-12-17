format long

fp = fopen('/media/vidigal/Dados/Git/tcctpv/pid/tb/tb_System_Matlab/setpoint.txt','w');
fprintf(fp, '%.6f\n', setpoint.Data);
fclose(fp);

fp = fopen('/media/vidigal/Dados/Git/tcctpv/pid/tb/tb_System_Matlab/output.txt','w');
fprintf(fp, '%.6f\n', output.Data);
fclose(fp);
format long

fp = fopen('/media/vidigal/Dados/Git/tcctpv/pid/tb/tb_PID_Matlab/error.txt','w');
fprintf(fp, '%.6f\n', error.Data);
fclose(fp);

fp = fopen('/media/vidigal/Dados/Git/tcctpv/pid/tb/tb_PID_Matlab/gain.txt','w');
fprintf(fp, '%.6f\n', gain.Data);
fclose(fp);
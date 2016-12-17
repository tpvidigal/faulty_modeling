format long

fp = fopen('/media/vidigal/Dados/Git/tcctpv/pid/tb/tb_Actuator/gain.txt','w');
fprintf(fp, '%.6f\n', gain.Data);
fclose(fp);

fp = fopen('/media/vidigal/Dados/Git/tcctpv/pid/tb/tb_Actuator/output.txt','w');
fprintf(fp, '%.6f\n', output.Data);
fclose(fp);
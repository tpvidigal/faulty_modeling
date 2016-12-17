format long

fp = fopen('/media/vidigal/Dados/Git/tcctpv/pid/tb/tb_PID_Matlab/error.txt','w');
for line = 1:5001
    binstr = dec2bin(typecast(error.Data(line), 'uint64'));
    while(size(binstr)<64)
        binstr = strcat('0', binstr);
    end
    fprintf(fp, binstr);
    fprintf(fp,'\n');
end
fclose(fp);

fp = fopen('/media/vidigal/Dados/Git/tcctpv/pid/tb/tb_PID_Matlab/gain.txt','w');
for line = 1:5001
    binstr = dec2bin(typecast(gain.Data(line), 'uint64'));
    while(size(binstr)<64)
        binstr = strcat('0', binstr);
    end
    fprintf(fp, binstr);
    fprintf(fp,'\n');
end
fclose(fp);
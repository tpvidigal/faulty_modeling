fsimplex = fopen('/media/vidigal/Dados/Git/tcctpv/pid/tb/tb_Reliability/time_to_fail_Simplex.txt','r');
ftmredun = fopen('/media/vidigal/Dados/Git/tcctpv/pid/tb/tb_Reliability/time_to_fail_TMR.txt','r');
ftmrsimp = fopen('/media/vidigal/Dados/Git/tcctpv/pid/tb/tb_Reliability/time_to_fail_TMRSimplex.txt','r');

% Read from files

simplex = cell2mat(textscan(fsimplex, '%f')) /1000;
tmredun = cell2mat(textscan(ftmredun, '%f')) /1000;
tmrsimp = cell2mat(textscan(ftmrsimp, '%f')) /1000;
M = length(simplex);

% Prepare data

count = 0;
t = 5:0.1:15;
p_simplex = zeros(1,length(t));
p_tmr     = zeros(1,length(t));
p_tmrsimplex = zeros(1,length(t));
for i = t
    count = count + 1;
    p_simplex   (count) = 1 - sum(simplex < i)/M;
    p_tmr       (count) = 1 - sum(tmredun < i)/M;
    p_tmrsimplex(count) = 1 - sum(tmrsimp < i)/M;
end

% Plots

figure
plot(t,p_simplex,'c',  t,p_tmr,'b',  t,p_tmrsimplex,'r' )
title('Reliability of PID implementations')
xlabel('time (s)')
ylabel('Reliability')
legend('Simplex', 'TMR', 'TMRSimplex')

fclose(fsimplex);
fclose(ftmredun);
fclose(ftmrsimp);
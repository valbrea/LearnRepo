% 计算有效吞吐量
function Throughput(SNR, slot)
loop = 50;
xaxis = 1 : 30 : slot;
A1_valid_throughput = zeros(loop, slot);
DFNC3_valid_throughput = zeros(loop, slot);
SNC3_valid_throughput = zeros(loop, slot);

A1_valid_mean = zeros(1, slot);
DFNC3_valid_mean = zeros(1, slot);
SNC3_valid_mean = zeros(1, slot);
for i = 1 : 1 : loop
    A1_valid_throughput(i, :) = A1_N3(SNR, slot);
    DFNC3_valid_throughput(i, :) = DFNC3(SNR, slot);
    SNC3_valid_throughput(i, :) = SNC3(SNR, slot);
end

A1_valid_mean = mean(A1_valid_throughput);
DFNC3_valid_mean = mean(DFNC3_valid_throughput);
SNC3_valid_mean = mean(SNC3_valid_throughput);


A1_N3_mean = A1_valid_mean(:, xaxis);
DFNC3_mean = DFNC3_valid_mean(:, xaxis);
SNC3_mean = SNC3_valid_mean(:, xaxis);

figure, hold on;
% , 'MarkerIndices', 1 : 60 : slot
plot (xaxis, A1_N3_mean, 'k-o');
% plot (xaxis, A2_mean, 'k-^');
plot (xaxis, DFNC3_mean, 'k-d');
plot (xaxis, SNC3_mean, 'k-s');

legend( 'A1', 'M-DF-NC', 'SNC-DM');
xlabel('仿真时隙数');
ylabel('传输吞吐量');
% title(['信噪比=', num2str(SNR), ', 循环次数=', num2str(loop)]);
end


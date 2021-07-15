% 计算有效吞吐量
function Throughput(SNR, slot)
loop = 50;
xaxis = 1 : 30 : slot;
throughput_upper_bound = zeros(loop, slot);
%A1_valid_throughput = zeros(loop, slot);
%A2_valid_throughput = zeros(loop, slot);
A3_valid_throughput = zeros(loop, slot);
DFNC3_valid_throughput = zeros(loop, slot);
SNC3_valid_throughput = zeros(loop, slot);

throughput_upper_bound_mean = zeros(1, slot);
%A1_valid_mean = zeros(1, slot);
%A2_valid_mean = zeros(1, slot);
A3_valid_mean = zeros(1, slot);
DFNC3_valid_mean = zeros(1, slot);
SNC3_valid_mean = zeros(1, slot);
for i = 1 : 1 : loop
    [throughput_upper_bound(i, :), ~, ~, ~] = A1_N3(SNR, slot);
    %[A2_valid_throughput(i, :), ~, ~] = A2_N3_old(SNR, slot);
    [A3_valid_throughput(i, :), ~, ~] = A3_N3(SNR, slot);
    [DFNC3_valid_throughput(i, :), ~, ~] = DFNC3(SNR, slot);
    [SNC3_valid_throughput(i, :), ~, ~] = SNC3(SNR, slot);
end

throughput_upper_bound_mean = mean(throughput_upper_bound);
%A1_valid_mean = mean(A1_valid_throughput);
%A2_valid_mean = mean(A2_valid_throughput);
A3_valid_mean = mean(A3_valid_throughput);
DFNC3_valid_mean = mean(DFNC3_valid_throughput);
SNC3_valid_mean = mean(SNC3_valid_throughput);

upper_bound_mean = throughput_upper_bound_mean(:, xaxis);
%A1_N3_mean = A1_valid_mean(:, xaxis);
%A2_N3_mean = A2_valid_mean(:, xaxis);
A3_N3_mean = A3_valid_mean(:, xaxis);
DFNC3_mean = DFNC3_valid_mean(:, xaxis);
SNC3_mean = SNC3_valid_mean(:, xaxis);

figure, hold on;
% , 'MarkerIndices', 1 : 60 : slot

plot (xaxis, upper_bound_mean, '-o');
%plot (xaxis, A1_N3_mean, '-+');
%plot (xaxis, A2_N3_mean, '-^');
plot (xaxis, A3_N3_mean, '-*');
plot (xaxis, DFNC3_mean, '-d');
plot (xaxis, SNC3_mean, '-s');

legend('吞吐量上界','本算法','M-DF-NC', 'SNC-DM');
xlabel('仿真时隙数');
ylabel('有效吞吐量');
title(['信噪比=', num2str(SNR),'dB']);
end


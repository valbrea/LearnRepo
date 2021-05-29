% 计算有效吞吐量
function valid(SNR, slot)
loop = 50;
xaxis = 1 : 30 : slot;
% A2_valid_throughput = zeros(loop, slot);
A3_valid_throughput = zeros(loop, slot);
DFNC4_valid_throughput = zeros(loop, slot);
SNC4_valid_throughput = zeros(loop, slot);

% A2_valid_mean = zeros(1, slot);
A3_valid_mean = zeros(1, slot);
DFNC4_valid_mean = zeros(1, slot);
SNC4_valid_mean = zeros(1, slot);
for i = 1 : 1 : loop
    A2_valid_throughput(i, :) = A2Network6(SNR, slot);
    A3_valid_throughput(i, :) = A3Network6 (SNR, slot);
%     A3_valid_throughput(i, :) = A3Network6_v2 (SNR, slot);
    DFNC4_valid_throughput(i, :) = DFNC4(SNR, slot);
    SNC4_valid_throughput(i, :) = SNC4(SNR, slot);
end

A2_valid_mean = mean(A2_valid_throughput);
A3_valid_mean = mean(A3_valid_throughput);
DFNC4_valid_mean = mean(DFNC4_valid_throughput);
SNC4_valid_mean = mean(SNC4_valid_throughput);

A2_mean = A2_valid_mean(:, xaxis);
A3_mean = A3_valid_mean(:, xaxis);
DFNC4_mean = DFNC4_valid_mean(:, xaxis);
SNC4_mean = SNC4_valid_mean(:, xaxis);

figure, hold on;
% , 'MarkerIndices', 1 : 60 : slot
plot (xaxis, A3_mean, 'k-o');
plot (xaxis, A2_mean, 'k-^');
plot (xaxis, DFNC4_mean, 'k-d');
plot (xaxis, SNC4_mean, 'k-s');

legend( '本发明', 'DF-NC-ARQ', 'M-DF-NC', 'SNC-DM');
xlabel('仿真时隙数');
ylabel('有效传输吞吐量');
% title(['信噪比=', num2str(SNR), ', 循环次数=', num2str(loop)]);
end


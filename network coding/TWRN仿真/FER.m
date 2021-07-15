function FER(slot)
EbN0_dB = 1 : 2 : 50;
% EbN0 = 10 .^(EbN0_dB / 10);
fer1 = zeros(1, length(EbN0_dB));
fer2 = zeros(1, length(EbN0_dB));
fer3 = zeros(1, length(EbN0_dB));
for q = 1 : length(EbN0_dB)
    [~, ~, fer1(q), ~] = A1_N3(q, slot);
    [~, fer2(q), ~] = A2_N3_old(q, slot);
    [~, fer3(q), ~] = A3_N3(q, slot);
end
figure
semilogy(EbN0_dB, fer1, '-o');
semilogy(EbN0_dB, fer2, '-*');
semilogy(EbN0_dB, fer3, '-s');
% grid on;
% axis([0 44 10^-5 10^-1]);
xlabel('Eb/N0 (dB)');
ylabel('FER');
legend('瑞利衰落信道下算法1仿真误帧率');
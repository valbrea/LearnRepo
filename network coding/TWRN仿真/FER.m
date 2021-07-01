function FER(slot)
EbN0_dB = 0 : 1 : 50;
% EbN0 = 10 .^(EbN0_dB / 10);
fer = zeros(1, length(EbN0_dB));
for q = 1 : length(EbN0_dB)
    [~, fer(q)] = A1_N3(q, slot);
end
figure
semilogy(EbN0_dB, fer, '-o');
% grid on;
% axis([0 44 10^-5 10^-1]);
xlabel('Eb/N0 (dB)');
ylabel('FER');
legend('瑞利衰落信道下算法1仿真误帧率');
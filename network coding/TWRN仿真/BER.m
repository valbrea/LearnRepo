% 计算BER
clc
clear
close all
% Title:BPSK系统在平坦瑞利衰落信道下的性能仿真
% Author：K.X.Song_HIT
% Data: 2019.03.26

L = 5000000;                            % 数据长度
data = round(rand(1,L));                % 原始数据
send = (data - 1/2) * 2;                % BPSK调制
EbN0_dB = 0:2:44;                       % Eb/N0 dB形式
EbN0 = 10.^(EbN0_dB/10);                % Eb/N0
Eb = 1;                                 % 每比特能量
N0 = Eb ./ EbN0;                        % 噪声功率
h = (randn(1,L) + 1j * randn(1,L)) / sqrt(2);       % 衰落因子
error = zeros(1,length(EbN0_dB));                   % 预置错误个数
ber = zeros(1,length(EbN0_dB));                     % 预置仿真误比特率
tber_bpsk = zeros(1,length(EbN0_dB));               % 预置理论误比特率
tber_bpsk_fading = zeros(1,length(EbN0_dB));        % 预置理论误比特率

for q = 1:length(EbN0_dB)
    noise = sqrt(N0(q)/2) * randn(1,L);     % 生成噪声
    receive = abs(h) .* send + noise;       % 接收信号
    detect = zeros(1,L);                % 预置检测信号
    % BPSK解调
    % 注：如果是其他调制方式，下面换成对应的解调方法即可
    for w = 1:L
        if (receive(w) >= 0)
            detect(w) = 1;              % 数轴右侧 ->  1
        else
            detect(w) = -1;             % 数轴左侧 -> -1
        end
        if (detect(w) ~= send(w))
            error(q) = error(q) + 1;    % 错误个数
        end
    end
    ber(q) = error(q) / L;                      % 仿真误比特率
    tber_bpsk(q) = erfc(sqrt(EbN0(q)))/2;       % AWGN信道下BPSK理论误比特率
    tber_bpsk_fading(q) = (1-sqrt(EbN0(q)/(1+EbN0(q))))/2;  % 瑞利衰落信道下BPSK理论误比特率
end
figure
semilogy(EbN0_dB,ber,'o',EbN0_dB,tber_bpsk_fading,'b',EbN0_dB,tber_bpsk,'r');
grid on;
axis([0 44 10^-5 10^-1])
xlabel('Eb/N0 (dB)');
ylabel('BER');
legend('瑞利衰落信道下BPSK仿真误码率','瑞利衰落信道下BPSK理论误码率','AWGN信道下BPSK理论误码率');

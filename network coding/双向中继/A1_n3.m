function [ throughput] = A1_n3(SNR, slot)
% 输入为SNR_dB和总的仿真时隙数
n = 3;
% 数据包大小
data_bits=100;
% 每个节点的初始数据为空
% PB
PB_A = zeros(1, data_bits);
PB_B = zeros(1, data_bits);
PB_C = zeros(1, data_bits);
PB_H = randn([0, 1], slot, data_bits);
PB_T = randn([0, 1], slot, data_bits);
% TB
TB_H = zeros(1, data_bits);
TB_T = zeros(1, data_bits);
% 接收缓存
Hreceive = zeros(1,data_bits);
Treceive = zeros(1,data_bits);
% 发送包的期望
Hsend = zeros(slot, data_bits);
Tsend = zeros(slot, data_bits);
% 其余数据
empty = zeros(1,data_bits);
prate = 11 * 10 ^ 6;   % 物理链路层速率
T = data_bits / prate; % 发送一次数据包所需时间
output = 0; % 总输出
valid = 0;  % 有效输出

hsend=0;
tsend=0;
hrecive=0;
trecive=0;
receive
for time=0:slot
    type=mod(time,3);
    switch type
        case 0
            %% 头节点H0发送
            % TB_H生成要发的包!!!!!!!!!!!!!!!!!!!!!!!!!!要改
            TB_H = randn([0, 1], 1, data_bits);
            % H向A传
            if ~isequal(TB_H, empty)
                Hsend(time, :) = TB_H; % 记录期望发送的包
                % 如果TB非空就发TB
                PB_A = xor(AR,BPSK(SNR, TB_H));
            else
                Hsend(time, :) = PB_H; % 记录期望发送的包
                PB_A = xor(AR, BPSK(SNR, PB_H)
                PB_H = xor(TB_H, PB_H); % 端节点每次传输前 异或TB和PB并放入PB中
            end
            %% 节点C3发送
            if ~isequal(PB_C3, empty)
                receive_B2 = BPSK(SNR, PB_C3);
                receive_T4 = BPSK(SNR, PB_C3);
                
                PB_B2 = xor(receive_B2, PB_B2);
                PB_T4 = xor(receive_T4, PB_T4);
                to_upper = PB_T4;
                if ~isequal(to_upper, empty)
                    output = output + 1;
                    if isequal(to_upper, Hsend(time - n, :));
                        % 判断n时刻前发的包是否和收到的包一致
                        valid = valid + 1;
                    end
                end
                PB_T4 = empty;
            end
            
            
        case 1
            %% 节点A1发送
            
            %% 尾节点T4发送
        case 2
            %% 节点B2发送
            
    end
    h=length(hrecive);
    t=length(trecive);
    hsend=hsend(:,2:t);
    hrecive=hrecive(:,2:h);
    tsend=tsend(:,2:h);
    trecive=trecive(:,2:t);
    delay=[trecive-hsend,hrecive-tsend];
    delay=mean(delay(:))+1;
    throughput=output/time;
end
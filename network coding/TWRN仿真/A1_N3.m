function [throughput, valid_throughput, FER, delay] = A1_N3(SNR, slot)
% 输入为SNR_dB和总的仿真时隙数
n = 3;
% 数据包大小
data_bits=8742;
% 每个节点的初始数据为空
% PB
PB_A1 = zeros(1, data_bits);
PB_B2 = zeros(1, data_bits);
PB_C3 = zeros(1, data_bits);
% 端节点PB里面是所有的待发送数据
PB_H0 = randi([0, 1], slot, data_bits);
PB_T4 = randi([0, 1], slot, data_bits);
% TB
TB_H0 = zeros(1, data_bits);
TB_T4 = zeros(1, data_bits);
% 接收到递交的包
H_receive = zeros(1,data_bits);
T_receive = zeros(1,data_bits);
% 发送包的期望
H_sent = [];
T_sent = [];


% 其余数据
empty = zeros(1, data_bits);
prate = 11 * 10 ^ 6;   % 物理链路层速率
T = data_bits / prate; % 发送一次数据包所需时间

output = 0; % 总接收到的数据包数量
valid = 0;  % 有效输出的数据包数量
error = 0;  % 错误的数据包数量
hsend = 0;
tsend = 0;
hrecive = 0;
trecive = 0;

% 接收缓存
cache_A1 = zeros(1, data_bits);
cache_B2 = zeros(1, data_bits);
cache_C3 = zeros(1, data_bits);
cache_H0 = zeros(1, data_bits);
cache_T4 = zeros(1, data_bits);

for time = 1:slot
    
    % 由于matlab时间只能从1开始，所以论文里time = 0, 3, 6 时发包的节点为H0, C3，仿真里在type = 1时候发包
    type = mod(time,3);
    switch type
        case 1
            %% 头节点H0发送
            % H向A传
            if ~isequal(TB_H0, empty)
                % 如果TB非空就发TB
                cache_A1 = BPSK(SNR, TB_H0);
                PB_A1 = XOR(PB_A1, cache_A1);
                hsend=[hsend,time];
            else
                cache_A1 = BPSK(SNR, PB_H0(1, :));
                PB_A1 = XOR(PB_A1, cache_A1);
                hsend=[hsend,time];
            end
            %% 节点C3发送
            % C向B和T传
            if ~isequal(PB_C3, empty) % 如果PB非空 发包
                % 中继B2收包
                cache_B2 = BPSK(SNR, PB_C3);
                PB_B2 = XOR(cache_B2, PB_B2);
                % 端节点T4收包
                % (5.1) 收包后和PB异或，XOR结果非空就递交
                cache_T4 = BPSK(SNR, PB_C3);
                T_receive = XOR(cache_T4, PB_T4(1, :));
                % (5.2) 如果非空就递交上层判断
                % 在 n + 1时刻以后T节点才会收到包
                if time >= (n + 1) && ~isequal(T_receive, empty)
                    output = output + 1;
                    if isequal(T_receive, H_sent(1, :))
                        % 判断n时刻前发的包是否和收到的包一致
                        valid = valid + 1;
                        trecive=[trecive,time];
                    else
                        error = error + 1;
                    end
                    % if ~isempty(H_sent)
                    H_sent(1, :) = [];
                end
                % (5.3)弹出PB第一个包
                T_sent(end + 1, :) = PB_T4(1, :); % 记录发送过的每个包y1,y2,y3...
                PB_T4(1, :) = []; % 弹出PB第一个
                TB_T4 = XOR(PB_T4(1, :), T_receive);
            end
        case 2
            %% 节点A1发送
            % A向H和B传
            if ~isequal(PB_A1, empty) % 如果PB非空 发包
                % 中继B2收包
                cache_B2 = BPSK(SNR, PB_A1);
                PB_B2 = XOR(cache_B2, PB_B2);
                % 端节点H0收包
                % (5.1) 收包后和PB异或，XOR结果非空就递交
                cache_H0 = BPSK(SNR, PB_A1);
                H_receive = XOR(cache_H0, PB_H0(1, :));
                % (5.2) 如果非空就递交上层判断
                % 在Tr = 2n + mod(n + 1, 3) + 1开始，H0节点才开始收到包，前面收到的都是回传信息
                if time >= (2 * n + mod(n + 1, 3) + 1) && ~isequal(H_receive, empty)
                    output = output + 1;
                    if isequal(H_receive, T_sent(1, :))
                        % 判断n时刻前发的包是否和收到的包一致
                        valid = valid + 1;
                        hrecive=[hrecive,time];
                    else
                        error = error + 1;
                    end
                    T_sent(1, :) = [];
                end
                % (5.3)弹出PB第一个包
                H_sent(end + 1, :) = PB_H0(1, :); % 记录发送过的每个包x1,x2,x3...
                PB_H0(1, :) = [];
                TB_H0 = XOR(PB_H0(1, :), H_receive);
            end
            %% 尾节点T4发送
            % T向C传
            if ~isequal(TB_T4, empty)
                % 如果TB非空就发TB
                cache_C3 = BPSK(SNR, TB_T4);
                PB_C3 = XOR(PB_C3, cache_C3);
                tsend=[tsend,time];
            else
                cache_C3 =  BPSK(SNR, PB_T4(1, :));
                PB_C3 = XOR(PB_C3, cache_C3);
                tsend=[tsend,time];
            end
        case 0
            %% 节点B2发送
            % B向A和C传
            if ~isequal(PB_B2, empty) % 如果PB非空 发包
                % 中继A1收包
                cache_A1 = BPSK(SNR, PB_B2);
                PB_A1 = XOR(cache_A1, PB_A1);
                % 中继C3收包
                cache_C3 = BPSK(SNR, PB_B2);
                PB_C3 = XOR(cache_C3, PB_C3);
            end
    end
    throughput(time) = output / time; % 吞吐量
    valid_throughput(time) = valid / time;  % 有效吞吐量
end
FER = error ./ output;
h=length(hrecive);
t=length(trecive);
hsend=hsend(:,2:t);
hrecive=hrecive(:,2:h);
tsend=tsend(:,2:h);
trecive=trecive(:,2:t);
delay=[trecive-hsend,hrecive-tsend];
delay=mean(delay(:))+1;

% figure, hold on;
% plot(throughput, 'r');
% plot(valid_throughput, 'b');
% xlabel('timeslot'), ylabel('throughput');
end
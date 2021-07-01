% function [throughput, FER] = A2_N3(SNR, slot)
function [] = A2_N3(SNR, slot)
% 输入为SNR_dB和总的仿真时隙数
n = 3;
% 数据包大小
data_bits=10;
% 每个节点的初始数据为空
% PB
PB_A1 = zeros(2, data_bits);
PB_B2 = zeros(2, data_bits);
PB_C3 = zeros(2, data_bits);
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
% 节点发包状态 0正常 1右传失败 2左传失败 3全失败
flag_H0 = 0;
flag_A1 = 0;
flag_B2 = 0;
flag_C3 = 0;
flag_T4 = 0;
% 其余数据
empty = zeros(1, data_bits);
prate = 11 * 10 ^ 6;   % 物理链路层速率
T = data_bits / prate; % 发送一次数据包所需时间

output = 0; % 总接收到的数据包数量
valid = 0;  % 有效输出的数据包数量
error = 0;  % 错误的数据包数量
% 接收缓存
cache_A1 = zeros(1, data_bits);
cache_B2 = zeros(1, data_bits);
cache_C3 = zeros(1, data_bits);
cache_H0 = zeros(1, data_bits);
cache_T4 = zeros(1, data_bits);
% hsend=0;
% tsend=0;
% hrecive=0;
% trecive=0;
% receive;
for time = 1:slot
    
    % 由于matlab时间只能从1开始，所以论文里time = 0, 3, 6 时发包的节点为H0, C3，仿真里在type = 1时候发包
    type = mod(time,3);
    switch type
        case 1
            %% 头节点H0发送
            % H向A传
            if ~isequal(TB_H0, empty)
                % 如果TB非空就发TB
                if ack_A1_H0 == 1 % 如果上次正常传输后收到了包(rule33)
                    cache_A1 = BPSK(SNR, TB_H0);
                    ack_H0_A1 = ACK(cache_A1, TB_H0);
                    if ack_H0_A1 == 1 % 传输成功
                        H_sent(end + 1, :) = PB_H0(1, :); % 记录发送过的每个包x1,x2,x3...
                        if ack_A1_B2 == 0 % 如果A1节点在往B重传的状态中
                            PB_A1(end, :) = cache_A1; % 存到PB末尾
                        else % 正常状态直接XOR到PB第一个
                            PB_A1(1, :) = XOR(PB_A1(1, :), cache_A1);
                        end
                    end % 传输失败的情况ack_H0_A1 = 0，会直接跳过这一时隙，直到下一个发送时隙
                end % rule33 A没发送数据包过来时
            else
                if ack_A1_H0 == 1 % 如果上一个时隙发送给A数据包，且A也发送了数据包回来，则正常发送
                    cache_A1 = BPSK(SNR, PB_H0(1, :));
                    ack_H0_A1 = ACK(cache_A1, PB_H0(1, :));
                    if ack_H0_A1 == 1 % 传输成功
                        H_sent(end + 1, :) = PB_H0(1, :); % 记录发送过的每个包x1,x2,x3...
                        if ack_A1_B2 == 0 % 如果A1节点在往B重传的状态中
                            PB_A1(end, :) = cache_A1; % 存到PB末尾
                        else % 正常状态直接XOR到PB第一个
                            PB_A1(1, :) = XOR(PB_A1(1, :), cache_A1);
                        end
                    end % 传输失败的情况ack_H0_A1 = 1，会直接跳过这一时隙，直到下一个发送时隙
                end % rule33 A没发送数据包过来时
            end
            %% 节点C3发送
            % C向B和T传
            if ~isequal(PB_C3(1, :), empty) % 如果PB非空
                % 上一个收信时隙收到了来自B2和T4的数据，C3才发包(rule33)
                if ack_T4_C3 == 1 && ack_B2_C3 == 1
                    % 传输过程是双向并发的
                    cache_B2 = BPSK(SNR, PB_C3(1, :));
                    cache_T4 = BPSK(SNR, PB_C3(1, :));
                     % 中继B2收包
                    ack_C3_B2 = ACK(cache_B2, PB_C3(1, :));
                    if ack_C3_B2 == 1
                        % 一旦传输(实际上是重传)成功后，就把PB合并
                        % 正常情况PB第二行是空的，不影响XOR操作
                        PB_C3(1, :) = XOR(PB_C3(1, :), PB_C3(end, :));
                        PB_C3(end, :) = empty;
                       if ack_B2_A1 == 0 % 如果B2在给A1的重传过程中
                           PB_B2(end, :) = cache_B2; 
                       else
                           PB_B2(1, :) = XOR(PB_B2(1, :), cache_B2);
                       end
                    end
                    % 端节点T4收包
                    % (5.1) 收包后和PB异或，XOR结果非空就递交

                    ack_C3_T4 = ACK(cache_T4, PB_C3(1, :));
                    if ack_C3_B2 == 1 % 端节点不用管rule32和33
                       PB_C3(1, :) = XOR(PB_C3(1, :), PB_C3(end, :));
                       PB_C3(end, :) = empty;
                       T_receive = XOR(cache_T4, PB_T4(1, :));
                    end
                    % (5.2) 如果非空就递交上层判断
                    % 在 n + 1时刻以后T节点才会收到包
                    if time >= (n + 1) && ~isequal(T_receive, empty) && ack_C3_T4 == 1
                        output = output + 1;
                        if ~isempty(H_sent)
                            if isequal(T_receive, H_sent(1, :))
                                % 判断n时刻前发的包是否和收到的包一致
                                valid = valid + 1;
                            else
                                error = error + 1;
                            end
                            % if ~isempty(H_sent)
                            H_sent(1, :) = [];
                        end
                    end
                    % (5.3)弹出PB第一个包
                    if ack_C3_T4 == 1 % 只有传输成功的时候才操作
                        PB_T4(1, :) = []; % 弹出PB第一个
                        TB_T4 = XOR(PB_T4(1, :), T_receive);
                    end
                end
            end
        case 2
            %% 节点A1发送
            % A向H和B传
            % 如果PB非空且上一个收信时隙收到了来自H0和B2的数据，C3才发包(rule33)
            if ~isequal(PB_A1(1, :), empty) 
                if ack_H0_A1 == 1 && ack_B2_A1 == 1 
                    % 传输过程是双向并发的
                    cache_B2 = BPSK(SNR, PB_A1(1, :));
                    cache_H0 = BPSK(SNR, PB_A1(1, :));
                    % 中继B2收包
                    ack_A1_B2 = ACK(cache_B2, PB_A1(1, :));
                    if ack_A1_B2 == 1
                        % 合并A1的PB
                        PB_A1(1, :) = XOR(PB_A1(1, :), PB_A1(end, :));
                        PB_A1(end, :) = empty;
                       if ack_B2_C3 == 0
                           PB_B2(end, :) = cache_B2;
                       else
                           PB_B2(1, :) = XOR(PB_B2(1, :), cache_B2);
                       end
                    end
                    % 端节点H0收包
                    % (5.1) 收包后和PB异或，XOR结果非空就递交
                    ack_A1_H0 = ACK(cache_H0, PB_A1(1, :));
                    if ack_A1_H0 == 1
                        PB_A1(1, :) = XOR(PB_A1(1, :), PB_A1(end, :));
                        PB_A1(end, :) = empty;
                        H_receive = XOR(cache_H0, PB_H0(1, :));
                    end
                    % (5.2) 如果非空就递交上层判断
                    % 在Tr = 2n + mod(n + 1, 3) + 1开始，H0节点才开始收到包，前面收到的都是回传信息
                    if time >= (2 * n + mod(n + 1, 3) + 1) && ~isequal(H_receive, empty) && ack_A1_H0 == 1
                        output = output + 1;
                        if ~isempty(T_sent)
                            if isequal(H_receive, T_sent(1, :))
                                % 判断n时刻前发的包是否和收到的包一致
                                valid = valid + 1;
                            else
                                error = error + 1;
                            end
                            T_sent(1, :) = [];
                        end
                    end
                    % (5.3)弹出PB第一个包
                    if ack_A1_H0 == 1 % 只有传输成功的时候才操作
                        PB_H0(1, :) = [];
                        TB_H0 = XOR(PB_H0(1, :), H_receive);
                    end
                end
            end
            %% 尾节点T4发送
            % T向C传
            if ~isequal(TB_T4, empty)
                % 如果TB非空就发TB
                if ack_C3_T4 == 1
                    cache_C3 = BPSK(SNR, TB_T4);
                    ack_T4_C3 = ACK(cache_C3, TB_T4);
                    if ack_T4_C3 == 1 % 传输成功
                        T_sent(end + 1, :) = PB_T4(1, :); % 记录发送过的每个包y1,y2,y3...
                        if ack_C3_B2 == 0 % 如果C3节点在往B2重传的状态中
                            PB_C3(end, :) = cache_C3; % 存到PB末尾
                        else % 正常状态直接XOR到PB第一个
                            PB_C3(1, :) = XOR(PB_C3(1, :), cache_C3);
                        end
                    end % 传输失败的情况ack_H0_A1 = 1，会直接跳过这一时隙，直到下一个发送时隙
                end
            else
                if ack_C3_T4 == 1
                    cache_C3 =  BPSK(SNR, PB_T4(1, :));
                    ack_T4_C3 = ACK(cache_C3, PB_T4(1, :));
                    if ack_T4_C3 == 1 % 传输成功
                        T_sent(end + 1, :) = PB_T4(1, :); % 记录发送过的每个包y1,y2,y3...
                        if ack_C3_B2 == 0 % 如果C3节点在往B2重传的状态中
                            PB_C3(end, :) = cache_C3; % 存到PB末尾
                        else % 正常状态直接XOR到PB第一个
                            PB_C3(1, :) = XOR(PB_C3(1, :), cache_C3);
                        end
                    end % 传输失败的情况ack_H0_A1 = 1，会直接跳过这一时隙，直到下一个发送时隙
                end
            end
        case 0
            %% 节点B2发送
            % B向A和C传
            % 如果PB非空且上一个收信时隙收到了来自A1和C3的数据，C3才发包(rule33)
            if ~isequal(PB_B2(1, :), empty) % 如果PB非空 发包
                % 如果两侧没有暂缓收包
                if  flag_A1 == 0 && flag_C3 == 0 
                    if flag_B2 == 1
                        % 右侧重传
                        [flag_B2, cache_C3] = TransRight(SNR, PB_B2(1, :));
                    elseif flag_B2 == 2
                        % 左侧重传
                        [flag_B2, cache_A1] = TransLeft(SNR, PB_B2(1, :));
                    else
                        % 传输过程是双向并发的
                        [flag_B2, cache_A1, cache_C3] = TransBi(SNR, PB_B2(1, :));
                    end
                end % 暂缓收包时直接直接不发
                % 中继A1收包
                if flag_B2 ~= 1 % 只要往A侧传了包
                    if flag_A1 == 2 % 如果A1节点在往H重传的状态中
                        PB_A1(end, :) = cache_A1; % 存到PB末尾
                    else % 正常状态直接XOR到PB第一个
                        PB_A1(1, :) = XOR(PB_A1(1, :), cache_A1);
                    end
                end % 传输失败的情况ack_B2_A1 = 0，会直接跳过这一时隙，直到下一个发送时隙
                % 中继C3收包
                if ack_B2_C3 == 1 % 传输成功
                    if ack_C3_T4 == 0 % 如果C3节点在往H重传的状态中
                        PB_C3(end, :) = cache_C3; % 存到PB末尾
                    else % 正常状态直接XOR到PB第一个
                        PB_C3(1, :) = XOR(PB_C3(1, :), cache_C3);
                    end
                end % 传输失败的情况ack_B2_C3 = 0，会直接跳过这一时隙，直到下一个发送时隙
                if ack_B2_A1 == 1 && ack_B2_C3 == 1
                    % 无论左重传还是右重传，只要最后重传成功以后，左右ack都应该是1，这时候就可以更新PB，并且取消暂缓接收的状态了
                    PB_B2(1, :) = XOR(PB_B2(1, :), PB_B2(end, :));
                    PB_B2(end, :) = empty;
                    pause_B2 = 1;
                end
            end
    end
    throughput(time) = output / time; % 吞吐量
    valid_throughput(time) = valid / time;  % 有效吞吐量
end
FER = error ./ output;
% h=length(hrecive);0
% t=length(trecive);
% hsend=hsend(:,2:t);
% hrecive=hrecive(:,2:h);
% tsend=tsend(:,2:h);
% trecive=trecive(:,2:t);
% delay=[trecive-hsend,hrecive-tsend];
% delay=mean(delay(:))+1;

figure, hold on;
plot(throughput, 'r');
plot(valid_throughput, 'b');
xlabel('timeslot'), ylabel('throughput');
end
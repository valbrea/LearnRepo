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
H_sent = PB_H0;
T_sent = PB_T4;
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
                cache_H0 = TB_H0;
            else
                cache_H0 = PB_H0(1, :);
            end
            if flag_A1 ~= 2 && flag_A1 ~= 3
                % 右侧重传或者正常发都一样
                [flag_H0, cache_A1] = TransRight(SNR, cache_H0);
                % else 暂缓收包时直接直接不发
            end
            % 中继A1收包
            if flag_H0 == 0 % 只要往A1侧发包成功
                if flag_A1 == 1 % 如果A1节点在往B重传的状态中
                    PB_A1(end, :) = cache_A1; % 存到PB末尾
                else % 正常状态直接XOR到PB第一个
                    PB_A1(1, :) = XOR(PB_A1(1, :), cache_A1);
                end
            end % 传输失败的情况，会直接跳过这一时隙，直到下一个发送时隙
            %% 节点C3发送
            % C向B和T传
            if ~isequal(PB_C3(1, :), empty) % 如果PB非空 发包
                % 如果C往BT发了以后，收到了B和T的回传包，才可以开始下一次发送(rule 33)
                if flag_B2 ~= 1 && flag_B2 ~= 3 && flag_T4 ~= 2
                    if flag_C3 == 1
                        % 右侧重传, 左成功
                        [flag_C3, cache_T4] = TransRight(SNR, PB_C3(1, :));
                    elseif flag_B2 == 2
                        % 左侧重传，右成功
                        [flag_C3, cache_B2] = TransLeft(SNR, PB_C3(1, :));
                    else
                        % 传输过程是双向并发的
                        [flag_C3, cache_B2, cache_T4] = TransBi(SNR, PB_C3(1, :));
                    end
                    % else 暂缓收包时直接直接不发
                end
                % 中继B2收包
                if flag_C3 == 0 || flag_C3 == 1 % 只要往B2侧发包成功
                    if flag_B2 == 2 % 如果B2节点在往A1重传的状态中
                        PB_B2(end, :) = cache_B2; % 存到PB末尾
                    else % 正常状态直接XOR到PB第一个
                        PB_B2(1, :) = XOR(PB_B2(1, :), cache_B2);
                    end
                end % 传输失败的情况，会直接跳过这一时隙，直到下一个发送时隙
                
                % 端节点T4收包
                if flag_C3 == 0 || flag_C3 == 2 % 只要往C侧发包成功
                    T_receive = XOR(cache_T4, PB_T4(1, :));
                end % 传输失败的情况，会直接跳过这一时隙，直到下一个发送时隙
                if flag_C3 == 0
                    % 无论左重传还是右重传，只要最后重传成功以后，flag都应该是0，这时候就可以更新合并PB。
                    PB_C3(1, :) = XOR(PB_C3(1, :), PB_C3(end, :));
                    PB_C3(end, :) = empty;
                end
                % (5.2) 如果非空就递交上层判断
                % 在 n + 1时刻以后T节点才会收到包
                if ~isequal(T_receive, empty) && (flag_C3 == 0 || flag_C3 == 2)
                    output = output + 1;
                    if isequal(T_receive, H_sent(1, :))
                        % 判断n时刻前发的包是否和收到的包一致
                        valid = valid + 1;
                    else
                        error = error + 1;
                    end
                    % if ~isempty(H_sent)
                    H_sent(1, :) = [];
                end
                % (5.3)弹出PB第一个包
                PB_T4(1, :) = []; % 弹出PB第一个
                TB_T4 = XOR(PB_T4(1, :), T_receive);
            end
        case 2
            %% 节点A1发送
            % A向H和B传
            if ~isequal(PB_A1(1, :), empty)
                % 如果A往HB发了以后，收到了H和B的回传包，才可以开始下一次发送(rule 33)
                if flag_H0 ~= 1 && flag_B2 ~= 2 && flag_B2 ~= 3
                    if flag_A1 == 1
                        % 右侧重传, 左成功
                        [flag_A1, cache_B2] = TransRight(SNR, PB_A1(1, :));
                    elseif flag_B2 == 2
                        % 左侧重传，右成功
                        [flag_A1, cache_H0] = TransLeft(SNR, PB_A1(1, :));
                    else
                        % 传输过程是双向并发的
                        [flag_A1, cache_H0, cache_B2] = TransBi(SNR, PB_A1(1, :));
                    end
                    % else 暂缓收包时直接直接不发
                end
                % 中继H0收包
                if flag_A1 == 0 || flag_A1 == 1 % 只要往H0侧发包成功
                    H_receive = XOR(cache_H0, PB_H0(1, :));
                end % 传输失败的情况，会直接跳过这一时隙，直到下一个发送时隙
                % 中继B2收包
                if flag_A1 == 0 || flag_A1 == 2 % 只要往B2侧发包成功
                    if flag_B2 == 1 % 如果C3节点在往T重传的状态中
                        PB_B2(end, :) = cache_B2; % 存到PB末尾
                    else % 正常状态直接XOR到PB第一个
                        PB_B2(1, :) = XOR(PB_B2(1, :), cache_B2);
                    end
                end % 传输失败的情况，会直接跳过这一时隙，直到下一个发送时隙
                if flag_A1 == 0
                    % 无论左重传还是右重传，只要最后重传成功以后，flag都应该是0，这时候就可以更新合并PB。
                    PB_A1(1, :) = XOR(PB_A1(1, :), PB_A1(end, :));
                    PB_A1(end, :) = empty;
                end
                
                % (5.2) 如果非空就递交上层判断
                % 在Tr = 2n + mod(n + 1, 3) + 1开始，H0节点才开始收到包，前面收到的都是回传信息
                if ~isequal(H_receive, empty) && (flag_A1 == 0 || flag_A1 == 1)
                    output = output + 1;
                    if isequal(H_receive, T_sent(1, :))
                        % 判断n时刻前发的包是否和收到的包一致
                        valid = valid + 1;
                    else
                        error = error + 1;
                    end
                    T_sent(1, :) = [];
                end
                % (5.3)弹出PB第一个包
                PB_H0(1, :) = [];
                TB_H0 = XOR(PB_H0(1, :), H_receive);
            end
            
            %% 尾节点T4发送
            % T向C传
            if ~isequal(TB_T4, empty)
                % 如果TB非空就发TB
                cache_T4 = TB_T4;
            else
                cache_T4 = PB_T4(1, :);
            end
            if flag_C3 ~= 2 && flag_C3 ~= 3
                % 右侧重传或者正常发都一样
                [flag_T4, cache_C3] = TransLeft(SNR, cache_T4);
                % else 暂缓收包时直接直接不发
            end
            % 中继C3收包
            if flag_T4 == 0 % 只要往C3侧发包成功
                if flag_C3 == 2 % 如果C3节点在往B重传的状态中
                    PB_C3(end, :) = cache_C3; % 存到PB末尾
                else % 正常状态直接XOR到PB第一个
                    PB_C3(1, :) = XOR(PB_C3(1, :), cache_C3);
                end
            end % 传输失败的情况，会直接跳过这一时隙，直到下一个发送时隙
        case 0
            %% 节点B2发送
            % B向A和C传
            % 如果PB非空
            if ~isequal(PB_B2(1, :), empty) % 如果PB非空 发包
                % 如果B往AC发了以后，收到了A和C的回传包，才可以开始下一次发送(rule 33)
                if flag_A1 ~= 1 && flag_A1 ~= 3 && flag_C3 ~= 2 && flag_C3 ~= 3
                    if flag_B2 == 1
                        % 右侧重传, 左成功
                        [flag_B2, cache_C3] = TransRight(SNR, PB_B2(1, :));
                    elseif flag_B2 == 2
                        % 左侧重传，右成功
                        [flag_B2, cache_A1] = TransLeft(SNR, PB_B2(1, :));
                    else
                        % 传输过程是双向并发的
                        [flag_B2, cache_A1, cache_C3] = TransBi(SNR, PB_B2(1, :));
                    end
                    % else 暂缓收包时直接直接不发
                end
                % 中继A1收包
                if flag_B2 == 0 || flag_B2 == 1 % 只要往A侧发包成功
                    if flag_A1 == 2 % 如果A1节点在往H重传的状态中
                        PB_A1(end, :) = cache_A1; % 存到PB末尾
                    else % 正常状态直接XOR到PB第一个
                        PB_A1(1, :) = XOR(PB_A1(1, :), cache_A1);
                    end
                end % 传输失败的情况，会直接跳过这一时隙，直到下一个发送时隙
                % 中继C3收包
                if flag_B2 == 0 || flag_B2 == 2 % 只要往C侧发包成功
                    if flag_C3 == 1 % 如果C3节点在往T重传的状态中
                        PB_C3(end, :) = cache_C3; % 存到PB末尾
                    else % 正常状态直接XOR到PB第一个
                        PB_C3(1, :) = XOR(PB_C3(1, :), cache_C3);
                    end
                end % 传输失败的情况，会直接跳过这一时隙，直到下一个发送时隙
                if flag_B2 == 0
                    % 无论左重传还是右重传，只要最后重传成功以后，flag都应该是0，这时候就可以更新合并PB。
                    PB_B2(1, :) = XOR(PB_B2(1, :), PB_B2(end, :));
                    PB_B2(end, :) = empty;
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
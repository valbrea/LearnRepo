% 思路： 给每个点分别设置传输标志，记录每段的传送成功或失败，最后接收的时候检查所有标志， 并统计有效吞吐量
function [ valid_throughput ] = A3Network6 (SNR, slot)
%数据包长度
data_bits=8472;
%每个节点的初始数据为空
AR=zeros(1,data_bits);
BR=zeros(1,data_bits);
CR=zeros(1,data_bits);
DR=zeros(1,data_bits);
%首节点与末节点所收到的初始数据为空
HR=zeros(1,data_bits);
TR=zeros(1,data_bits);
H2T=zeros(1,data_bits);
T2H=zeros(1,data_bits);
Htemp = zeros(1,data_bits);
Ttemp = zeros(1,data_bits);
%其余数据
throughput = zeros(1, slot);
valid_throughput = zeros(1, slot);
output = 0; % 输出数量
% 每次传输错误包数量
left_error = 0; % 左传错误数量
right_error = 0;
valid = 0; % 有效输出
empty=zeros(1,data_bits);%置零
% 传输标志 成功0 右1 左2 均3
FLAG = zeros(1, 6); % 6个节点012345的传输标志依次
for i = 1 : 6
    
end
for time=1:slot %仿真时间
    type=mod(time,3); %将网络中的节点分为三类
    switch type
        case 0 %第2 5个节点发送数据
            % B节点发送
            AR=xor(AR,BPSK(SNR, BR)); % B向A传
            CR=xor(CR,BPSK(SNR, BR)); % B向C传
            FLAG(3) = TRANS2(SNR, BR);
        
            % T节点发送
            T2H=randi([0,1],1,data_bits); % 每次发送前都随机生成Y1，Y2，Y3数据包
            DR=xor(DR,BPSK(SNR, T2H)); % T向D传
            FLAG(6) = TRANSL(SNR, T2H);
            TR = xor(T2H, TR); % 端节点每次传输前 异或TB和PB并放入PB中
            
        case 1 %第0 3个节点发送数据
            % H节点发送
            H2T = randi([0,1],1,data_bits); % 每次发送前都随机生成X1，X2，X3数据包
            AR = xor(AR, BPSK(SNR, H2T));
            FLAG(1) = TRANSR(SNR, BR);
            HR = xor(H2T, HR); % 端节点每次传输前 异或TB和PB并放入PB中 

            % C节点发送
            BR=xor(BPSK(SNR, CR), BR);
            DR=xor(BPSK(SNR, CR), DR);
            FLAG(4) = TRANS2(SNR, CR);
        case 2 %第1 4个节点发送数据
            % A节点发送
            BR=xor(BR, BPSK(SNR, AR));
            Htemp = xor(HR, BPSK(SNR, AR)); % H接收到的包和HR的异或结果
            FLAG(2) = TRANS2(SNR, AR);
            if ~isequal(AR, empty) && ~isequal(Htemp, empty) % 如果接收到的包和HR异或后不为空
                output = output + 1; % 递交XOR的结果给上层协议（输出+1)
                % 检查H节点收到的包在向左传输过程中是否有错
                for i = 1 : 1 : 6
                    switch FLAG(i) 
                        case 2 % 如果左传有错(case2) 错误+1(多节点出错只计算一次）
                            left_error = 1; 
                            FLAG(i) = 0;
                        case 3 % 如果有双侧错误 两种错误+1 
                            left_error = 1;
                            right_error = 1;
                            FLAG(i) = 0; % 避免重复计算 一定要清零
                    end
                end
                valid = valid + 1 - left_error;% 只扣除左侧错误 右侧错误已经计数，但是留到T节点接收的时候再统计；
                left_error = 0; % 只清零左侧错误
            end
            HR = BPSK(SNR, AR); % 把HR更新成这个接收到的包
            AR = empty; % A节点发送后PB清空
            % D节点发送
            CR=xor(CR, BPSK(SNR, DR));
            Ttemp = xor(TR, BPSK(SNR, DR));
            FLAG(5) = TRANS2(SNR, DR);
            if ~isequal(DR, empty) && ~isequal(Ttemp, empty)
                output = output + 1;
                % 检查T节点收到的包在向右传输过程中是否有错
                for i = 1 : 1 : 6
                    switch FLAG(i) 
                        case 1 % 如果右传有错(case1) 错误+1(多节点出错只计算一次）
                            right_error = 1; 
                            FLAG(i) = 0;
                        case 3 % 如果有双侧错误 两种错误+1 
                            left_error = 1;
                            right_error = 1;
                            FLAG(i) = 0; % 避免重复计算 一定要清零
                    end
                end
                valid = valid + 1 - right_error;
                right_error = 0; % 只清零右侧错误
            end
            TR = BPSK(SNR, DR);
            DR = empty; % D发送后PB清空
    end
    throughput(time) = output / (time + 1);
    valid_throughput(time) = valid / (time + 1);
    
end
% figure, hold on;
% plot(throughput, 'r');
% plot(valid_throughput, 'b');
% % xlabel('timeslot'), ylabel('throughput');
end
% 思路2： N = 4个时隙后收到数据包，检测是否和发送期望相等，相等则有效吞吐量+1
function [ valid_throughput ] = A3Network6_v2 (SNR, slot)
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
% 接收缓存
Hreceive = zeros(1,data_bits); 
Treceive = zeros(1,data_bits);
% 发送期望
Hsend = zeros(slot + 4, data_bits);
Tsend = zeros(slot + 4, data_bits);
%其余数据
throughput = zeros(1, slot);
valid_throughput = zeros(1, slot);
output = 0; % 输出数量
% % 每次传输错误包数量
% left_error = 0; % 左传错误数量
% right_error = 0;
valid = 0; % 有效输出
empty=zeros(1,data_bits);%置零


for time=1:slot %仿真时间
    type=mod(time,3); %将网络中的节点分为三类
    switch type
        case 0 %第2 5个节点发送数据
            % B节点发送
            AR=xor(AR,BPSK(SNR, BR)); % B向A传
            CR=xor(CR,BPSK(SNR, BR)); % B向C传
        
            % T节点发送
            T2H=randi([0,1],1,data_bits); % 每次发送前都随机生成Y1，Y2，Y3数据包
            Tsend(time + 4, :) = T2H;
            DR=xor(DR,BPSK(SNR, T2H)); % T向D传
         
            TR = xor(T2H, TR); % 端节点每次传输前 异或TB和PB并放入PB中
            
        case 1 %第0 3个节点发送数据
            % H节点发送
            H2T = randi([0,1],1,data_bits); % 每次发送前都随机生成X1，X2，X3数据包
            Hsend(time + 4, :) = H2T;
            AR = xor(AR, BPSK(SNR, H2T));
            
            HR = xor(H2T, HR); % 端节点每次传输前 异或TB和PB并放入PB中 

            % C节点发送
            BR=xor(BPSK(SNR, CR), BR);
            DR=xor(BPSK(SNR, CR), DR);

        case 2 %第1 4个节点发送数据
            % A节点发送
            BR=xor(BR, BPSK(SNR, AR));
            Hreceive = xor(HR, BPSK(SNR, AR)); % H接收到的包和HR的异或结果

            if ~isequal(AR, empty) && ~isequal(Hreceive, empty) % 如果接收到的包和HR异或后不为空
                output = output + 1; % 递交XOR的结果给上层协议（输出+1)
                if isequal(Tsend(time, :), Hreceive)
                    valid = valid + 1;
                end
            end
            HR = BPSK(SNR, AR); % 把HR更新成这个接收到的包
            AR = empty; % A节点发送后PB清空
            % D节点发送
            CR=xor(CR, BPSK(SNR, DR));
            Treceive = xor(TR, BPSK(SNR, DR));

            if ~isequal(DR, empty) && ~isequal(Treceive, empty)
                output = output + 1;
                if isequal(Hsend(time, :), Treceive)
                    valid = valid + 1;
                end
            end
            TR = BPSK(SNR, DR);
            DR = empty; % D发送后PB清空
    end
    throughput(time) = output / (time + 1);
    valid_throughput(time) = valid / (time + 1);
    
end
figure, hold on;
plot(throughput, 'r--');
plot(valid_throughput, 'b--');
xlabel('timeslot'), ylabel('throughput');
end
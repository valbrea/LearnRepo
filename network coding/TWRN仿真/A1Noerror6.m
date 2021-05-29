function [throughput] = A1Noerror6 (slot)
%数据包长度
data_bits = 8472;
%每个节点的初始数据为空
AR = zeros(1, data_bits);
BR = zeros(1, data_bits);
CR = zeros(1, data_bits);
DR = zeros(1, data_bits);
%首节点与末节点所收到的初始数据为空
HR = zeros(1, data_bits);
TR = zeros(1, data_bits);
H2T = zeros(1, data_bits);
T2H = zeros(1, data_bits);
%其余数据
throughput = zeros(1, slot);
output = 0;
empty = zeros(1, data_bits); %置零

for time = 1:slot %仿真时间
    type = mod(time, 3); %将网络中的节点分为三类
    
    switch type
        case 0 %第2 5个节点发送数据
            % B节点
            AR = xor(AR, BR); % B向A传
            CR = xor(CR, BR); % B向C传
            T2H = randi([0, 1], 1, data_bits); % 每次发送前都随机生成Y1，Y2，Y3数据包
            
            if TR == empty
                TR = T2H;
            else TR = xor(T2H, TR);
            end
            
            DR = xor(DR, TR); % T向D传
            
        case 1 %第0 3个节点发送数据
            H2T = randi([0, 1], 1, data_bits); % 每次发送前都随机生成X1，X2，X3数据包
            
            if HR == empty
                HR = H2T; % 把要发送的数据弹入TB
            else HR = xor(H2T, HR); % 把要发送的数据弹入TB
            end
            
            AR = xor(AR, HR);
            
            BR = xor(CR, BR);
            DR = xor(CR, DR);
            
        case 2 %第1 4个节点发送数据
            BR = xor(BR, AR);
            HR = xor(H2T, AR);
            
            if ~isequal(AR, empty) &&~isequal(HR, empty)
                output = output + 1;
            end
            
            CR = xor(CR, DR);
            TR = xor(T2H, DR);
            
            if ~isequal(DR, empty) &&~isequal(xor(DR, T2H), empty)
                output = output + 1;
            end
            
    end
    
    throughput(time) = output / (time + 1);
end

% figure;
% plot(throughput, 'r');
% xlabel('timeslot'), ylabel('throughput');
end

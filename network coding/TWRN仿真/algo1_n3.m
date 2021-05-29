function[out] = algo1_n3(SNR_dB, slot)
%%
%数据包大小
n = 3;
data_bits = 100;
output=0;

empty=zeros(1, data_bits);
prate=11 * 10 ^ 6; %物理链路层速率
T = data_bits / prate; %发送一次数据包所需时间
% 头节点
head = EndNode(0, data_bits);
tail = EndNode(n + 1, data_bits);

% 所有节点
node = {head, RelayNode(1, data_bits), RelayNode(2, data_bits), RelayNode(3, data_bits), tail};

%%

for time = 0 : slot
    type = mod(time, 3);
    switch type
        case 0
            % head,node3发包
            
        case 1
            %
        case 2
    end
end

    
    

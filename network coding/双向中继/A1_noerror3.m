function [ throughput ] = A1Noerror5 (slot )

data_bits = 8472;
%每个节点的初始数据为空
AR=zeros(1,data_bits);
BR=zeros(1,data_bits);
CR=zeros(1,data_bits);
%首节点与末节点所收到的初始数据为空
HR=zeros(1,data_bits);
TR=zeros(1,data_bits);
H2T=zeros(1,data_bits);
T2H=zeros(1,data_bits);
%其余数据
throughput=0;
output=0;
empty=zeros(1,data_bits);%置零

for time = 1 : slot %仿真时间
    type = mod(time,3); %将网络中的节点分为三类
    switch type
        case 0 %第2个节点发送数据
            AR=xor(AR,BR);
            CR=xor(CR,BR);
      
            
        case 1 %第0 3个节点发送数据
            H2T=randi([0,1],1,data_bits);
            if HR==empty
                HR=H2T;
            else
                HR=xor(H2T,HR);
            end
            AR=xor(AR,HR);
            
            BR=xor(CR,BR);
            if ~isequal(CR,empty)&&~isequal(xor(CR,T2H),empty)
                output=output+1;
            end
            
        case 2 %第1 4个节点发送数据
            BR=xor(BR,AR);
            HR=xor(H2T,AR);
            if ~isequal(AR,empty)&&~isequal(HR,empty)
                output=output+1;
            end
            
            T2H=randi([0,1],1,data_bits);
            if TR==empty
                TR=T2H;
            else
                TR=xor(T2H,TR);
            end
            AR=xor(AR,TR);

    end
    throughput(time)=output/(time+1);
end
figure;
plot(throughput, 'r');
xlabel('timeslot'), ylabel('throughput');
end
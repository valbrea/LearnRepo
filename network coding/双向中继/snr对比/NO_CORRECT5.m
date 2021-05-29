function [ throughput ] = NO_CORRECT5(SNR)
data_bits=100;
X1=randi([0,1],1,data_bits);
X2=randi([0,1],1,data_bits);
X3=randi([0,1],1,data_bits);
Y1=randi([0,1],1,data_bits);
Y2=randi([0,1],1,data_bits);
Y3=randi([0,1],1,data_bits);

headinput=[0,X3];
headoutput=0;
tailinput=[0,Y2,Y3]; 
tailoutput=0;

HR=Y1;
AR=XOR(X3,Y1);
BR=XOR(X3,Y2);
CR=XOR(Y2,Y3);
TR=Y3;

slot=14;

for time=0:slot %仿真时间
    type=mod(time,3); %将网络中的节点分为三类
    switch type
        case 0 %第2个节点发送数据
            B2R=BPSK(SNR,BR);
            AR=XOR(AR,B2R);
            CR=XOR(CR,B2R);
      
        case 1 %第0 3个节点发送数据
            H2T=randi([0,1],1,data_bits);
            headinput=[headinput,H2T];
            HR=XOR(HR,H2T);
            H2R=BPSK(SNR,HR);
            AR=XOR(AR,H2R);
            HR=H2T;
            
            C2R=BPSK(SNR,CR);
            BR=XOR(BR,C2R);
            TR=XOR(TR,C2R);
            tailoutput=[tailoutput,TR];
            
        case 2 %第1 4个节点发送数据
            A2R=BPSK(SNR,AR);
            BR=XOR(BR,A2R);
            HR=XOR(HR,A2R);
            headoutput=[headoutput,HR];
            
            T2H=randi([0,1],1,data_bits);
            tailinput=[tailinput,T2H];
            TR=XOR(TR,T2H);
            T2R=BPSK(SNR,TR);
            CR=XOR(CR,T2R);
            TR=T2H;                    
    end   
end
A=length(tailoutput);
tailoutput=tailoutput(:,2:A);
headinput=headinput(:,2:A);
B=length(headoutput);
headoutput=headoutput(:,2:B);
tailinput=tailinput(:,2:B);
validpacket=COUNT1(headinput,tailoutput,data_bits)+COUNT1(tailinput,headoutput,data_bits);
throughput=validpacket/(slot+1);
end


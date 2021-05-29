function [ throughput ] = NO_MDFNC7(SNR)
data_bits=100;
X1=randi([0,1],1,data_bits);
Y1=randi([0,1],1,data_bits);
headinput=[0,X1];
headoutput=0;
tailinput=[0,Y1]; 
tailoutput=0;
HR=zeros(1,data_bits);
TR=zeros(1,data_bits);
AR=zeros(1,data_bits);
BR=X1;
CR=XOR(X1,Y1);
DR=Y1;
ER=zeros(1,data_bits);

slot=1000;

for time=0:slot 
    type=mod(time,5);
    switch type
        case 0
            HR=randi([0,1],1,data_bits);
            headinput=[headinput,HR];
            H2R=BPSK(SNR,HR);
            AR=XOR(AR,H2R);
            TR=randi([0,1],1,data_bits);
            tailinput=[tailinput,TR];
            T2R=BPSK(SNR,TR);
            ER=XOR(T2R,ER);
            
            C2R=BPSK(SNR,CR);
            BR=XOR(BR,C2R);
            DR=XOR(DR,C2R);
            CR=zeros(1,data_bits);
            
        case 1
            B2R=BPSK(SNR,BR);
            AR=XOR(B2R,AR);
 
            D2R=BPSK(SNR,DR);
            ER=XOR(D2R,ER);
            
        case 2
            A2R=BPSK(SNR,AR);
            BR=XOR(BR,A2R);
            HR=XOR(HR,A2R);
            headoutput=[headoutput,HR];
            AR=zeros(1,data_bits);
            
            E2R=BPSK(SNR,ER);
            DR=XOR(DR,E2R);
            TR=XOR(TR,E2R);
            tailoutput=[tailoutput,TR];
            ER=zeros(1,data_bits);
            
        case 3
            B2R=BPSK(SNR,BR);
            CR=XOR(CR,B2R);
            
        case 4
            D2R=BPSK(SNR,DR);
            CR=XOR(CR,D2R);
    end
        
end
A=length(tailoutput);
tailoutput=tailoutput(:,2:A);
headinput=headinput(:,2:A);
B=length(headoutput);
headoutput=headoutput(:,2:B);
tailinput=tailinput(:,2:B);
validpacket=COUNT1(headinput,tailoutput,data_bits)+COUNT1(tailinput,headoutput,data_bits);
throughput=validpacket/slot;
end
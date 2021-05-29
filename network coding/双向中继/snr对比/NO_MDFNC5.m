function [ throughput ] = NO_MDFNC5(SNR)
data_bits=100;
headinput=0;
headoutput=0;
tailinput=0; 
tailoutput=0;
HR=zeros(1,data_bits);
TR=zeros(1,data_bits);
AR=zeros(1,data_bits);
BR=zeros(1,data_bits);
CR=zeros(1,data_bits);

slot=180;

for time=0:slot 
    type=mod(time,5);
    switch type
        case 0
            H2T=randi([0,1],1,data_bits);
            headinput=[headinput,H2T];
            HR=XOR(H2T,HR);
            H2R=BPSK(SNR,HR);
            AR=XOR(AR,H2R);
            T2H=randi([0,1],1,data_bits);
            tailinput=[tailinput,T2H];
            TR=XOR(T2H,TR);
            T2R=BPSK(SNR,TR);
            CR=XOR(T2R,CR);
            
        case 1
            A2R=BPSK(SNR,AR);
            BR=XOR(BR,A2R);
            
        case 2
            C2R=BPSK(SNR,CR);
            BR=XOR(BR,C2R);
            
        case 3
            B2R=BPSK(SNR,BR);
            BR=zeros(1,data_bits);
            AR=XOR(AR,B2R);
            CR=XOR(CR,B2R);
            
        case 4
            A2R=BPSK(SNR,AR);
            headoutput=[headoutput,A2R];
            HR=A2R;
            C2R=BPSK(SNR,CR);
            tailoutput=[tailoutput,C2R];
            TR=C2R;
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
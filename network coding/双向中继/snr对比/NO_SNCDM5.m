function [ throughput ] = NO_SNCDM5(SNR)
data_bits=100;

HR=zeros(1,data_bits);
TR=zeros(1,data_bits);
AR=zeros(1,data_bits);
BR=zeros(1,data_bits);
CR=zeros(1,data_bits);

X1=randi([0,1],1,data_bits);
X2=randi([0,1],1,data_bits);
Y1=randi([0,1],1,data_bits);
Y2=randi([0,1],1,data_bits);
Y3=randi([0,1],1,data_bits);

headinput=[0,X1,X2];
headoutput=0;
tailinput=[0,Y1,Y2]; 
tailoutput=0;

CR=XOR(BPSK(SNR,Y2),BPSK(SNR,BPSK(SNR,BPSK(SNR,X1))));
BR=XOR(BPSK(SNR,BPSK(SNR,X1)),BPSK(SNR,BPSK(SNR,Y1)));
AR=XOR(BPSK(SNR,X2),BPSK(SNR,BPSK(SNR,BPSK(SNR,Y1))));
HR=X2;
TR=Y2;

C2R=BPSK(SNR,CR);
BR=XOR(C2R,BR);
TR=XOR(C2R,TR);
tailoutput=[tailoutput,TR];

slot=200;

for time=0:slot 
    type=mod(time,4);
    switch type
        case 0
            A2R=BPSK(SNR,AR);
            HR=XOR(A2R,HR);
            headoutput=[headoutput,HR];
            BR=XOR(A2R,BR);
            
        case 1
            H2T=randi([0,1],1,data_bits);
            headinput=[headinput,H2T];
            H2R=BPSK(SNR,XOR(H2T,HR));
            AR=XOR(AR,H2R);
            HR=H2T;
            T2H=randi([0,1],1,data_bits);
            tailinput=[tailinput,T2H];
            T2R=BPSK(SNR,XOR(T2H,TR));
            CR=XOR(CR,T2R);
            TR=T2H;
            
        case 2
            B2R=BPSK(SNR,BR);
            AR=XOR(AR,B2R);
            CR=XOR(CR,B2R);
            
        case 3
            C2R=BPSK(SNR,CR);
            TR=XOR(TR,C2R);
            tailoutput=[tailoutput,TR];
            BR=XOR(BR,C2R);
            
    end
end
A=length(tailoutput);
tailoutput=tailoutput(:,2:A);
headinput=headinput(:,2:A);
B=length(headoutput);
headoutput=headoutput(:,2:B);
tailinput=tailinput(:,2:B);
validpacket=COUNT1(headinput,tailoutput,data_bits)+COUNT1(tailinput,headoutput,data_bits);
throughput=validpacket/(slot+7);        

end
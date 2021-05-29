function [ throughput ] = NO_SNCDM(SNR)
data_bits=100;

X1=randi([0,1],1,data_bits);
X2=randi([0,1],1,data_bits);
Y1=randi([0,1],1,data_bits);
Y2=randi([0,1],1,data_bits);


headinput=[0,X1,X2];
headoutput=0;
tailinput=[0,Y1,Y2]; 
tailoutput=0;

H=X2;
T=Y2;

AL=X2;
A2L=X2;
AR=Y1;
A2R=Y1;
BL=X1;
BR=Y1;
C2L=X1;
C2R=Y2;


slot=1000;

for time=0:slot 
    type=mod(time,4);
    switch type
        case 0
            C2=BPSK(SNR,XOR(C2R,C2L));
            CR=C2R;
            CL=C2L;
            T=XOR(C2,T);
            tailoutput=[tailoutput,T];
            B2R=XOR(C2,BL);
               
        case 1
            A2=BPSK(SNR,XOR(A2R,A2L));
            H=XOR(A2,H);
            headoutput=[headoutput,H];
            B2L=XOR(A2,BR);
    
        case 2
            H=randi([0,1],1,data_bits);
            headinput=[headinput,H];
            H2=BPSK(SNR,H);
            A2L=H2;
            T=randi([0,1],1,data_bits);
            tailinput=[tailinput,T];
            T2=BPSK(SNR,T);
            C2R=T2;
            
        case 3
            B2=BPSK(SNR,XOR(B2R,B2L));
            BR=B2R;
            BL=B2L;
            A2R=XOR(B2,AL);
            AL=A2L;
            C2L=XOR(B2,CR);
            CR=C2R;
    end
end
A=length(tailoutput);
tailoutput=tailoutput(:,2:A);
headinput=headinput(:,2:A);
B=length(headoutput);
headoutput=headoutput(:,2:B);
tailinput=tailinput(:,2:B);
validpacket=COUNT1(headinput,tailoutput,data_bits)+COUNT1(tailinput,headoutput,data_bits);
throughput=validpacket/(slot+6); 
function [ ber ] = ber6(snr)
data_bits=1000000;
AR=zeros(1,data_bits);
BR=zeros(1,data_bits);
CR=zeros(1,data_bits);
DR=zeros(1,data_bits);
HR=zeros(1,data_bits);
TR=zeros(1,data_bits);

X1=randi([0,1],1,data_bits);
H2R=bpsk(snr,X1);
AR=H2R;
C2R=bpsk(snr,CR);
BR=double(xor(BR,C2R));
DR=double(xor(DR,C2R));

A2R=bpsk(snr,AR);
BR=double(xor(A2R,BR));
D2R=bpsk(snr,DR);
CR=double(xor(D2R,CR));
TR=double(xor(D2R,TR));

Y1=randi([0,1],1,data_bits);
T2R=bpsk(snr,double(xor(TR,Y1)));
DR=double(xor(T2R,DR));
B2R=bpsk(snr,BR);
CR=double(xor(B2R,CR));

C2R=bpsk(snr,CR);
DR=double(xor(C2R,DR));

D2R=bpsk(snr,DR);
data=double(xor(Y1,D2R));

ber=biterr(data,X1)/data_bits;

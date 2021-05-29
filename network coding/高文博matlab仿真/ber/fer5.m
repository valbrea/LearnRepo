function [ fer ] = fer5(snr)
data_bits=100;
AR=zeros(1,data_bits);
BR=zeros(1,data_bits);
CR=zeros(1,data_bits);
HR=zeros(1,data_bits);
TR=zeros(1,data_bits);

X1=randi([0,1],1,data_bits);
H2R=bpsk(snr,X1);
AR=H2R;
C2R=bpsk(snr,CR);
BR=double(xor(BR,C2R));
TR=double(xor(TR,C2R));

A2R=bpsk(snr,AR);
BR=double(xor(A2R,BR));
Y1=randi([0,1],1,data_bits);
T2R=bpsk(snr,Y1);
CR=double(xor(T2R,CR));

B2R=bpsk(snr,BR);
CR=double(xor(B2R,CR));

C2R=bpsk(snr,CR);
data=double(xor(Y1,C2R));

if biterr(data,X1)>=1
    fer=1;
else
    fer=0;
end
end

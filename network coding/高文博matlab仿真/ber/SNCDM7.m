function [fer] = SNCDM7(snr)
data_bits=100;
X0=randi([0,1],1,data_bits);
Y1=randi([0,1],1,data_bits);
Y2=randi([0,1],1,data_bits);
Y3=randi([0,1],1,data_bits);
AR=X0;
GR=Y1;
BR=bpsk(snr,AR);
CR=bpsk(snr,BR);
DR=bpsk(snr,CR);
FR=bpsk(snr,GR);
ER=bpsk(snr,FR);
DR=double(xor(bpsk(snr,ER),DR));
ER=double(xor(bpsk(snr,DR),ER));
GR=Y2;
FR=bpsk(snr,GR);
ER=double(xor(bpsk(snr,FR),ER));
FR=double(xor(bpsk(snr,ER),FR));
GR=Y3;
FR=double(xor(bpsk(snr,GR),FR));
data=double(xor(bpsk(snr,FR),GR));
if biterr(data,X0)>=1
    fer=1;
else
    fer=0;
end
end
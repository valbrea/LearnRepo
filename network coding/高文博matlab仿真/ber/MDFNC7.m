function [fer] = MDFNC7(snr)
data_bits=100;
X1=randi([0,1],1,data_bits);
X2=randi([0,1],1,data_bits);
Y1=randi([0,1],1,data_bits);
Y2=randi([0,1],1,data_bits);
AR=X1;
BR=bpsk(snr,AR);
CR=bpsk(snr,BR);
DR=bpsk(snr,CR);
GR=Y1;
FR=bpsk(snr,GR);
ER=bpsk(snr,FR);
DR=double(xor(DR,bpsk(snr,ER)));
ER=double(xor(ER,bpsk(snr,DR)));
GR=Y2;
FR=bpsk(snr,GR);
FR=double(xor(FR,bpsk(snr,ER)));
data=double(xor(GR,bpsk(snr,FR)));
if biterr(data,X1)>=1
    fer=1;
else
    fer=0;
end
end

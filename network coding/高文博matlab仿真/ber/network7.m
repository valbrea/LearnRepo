function [fer] = network7(snr)
data_bits=100;
X1=randi([0,1],1,data_bits);
Y1=randi([0,1],1,data_bits);
Y2=randi([0,1],1,data_bits);
Y3=randi([0,1],1,data_bits);

AR=X1;
GR=Y1;
BR=bpsk(snr,AR);
FR=bpsk(snr,GR);
CR=bpsk(snr,BR);
DR=bpsk(snr,CR);
ER=bpsk(snr,FR);
ER=double(xor(bpsk(snr,DR),ER));
GR=Y2;
FR=double(xor(bpsk(snr,GR),FR));
FR=double(xor(bpsk(snr,ER),FR));
data=double(xor(bpsk(snr,FR),Y2));
if biterr(data,X1)>=1
    fer=1;
else
    fer=0;
end
end


function [ber] = MDFNC5(snr)
data_bits=100;
X1=randi([0,1],1,data_bits);
X2=randi([0,1],1,data_bits);
Y1=randi([0,1],1,data_bits);
Y2=randi([0,1],1,data_bits);
AR=X2;
BR=bpsk(snr,X1);
CR=bpsk(snr,BR);
ER=Y1;
DR=double(xor(bpsk(snr,CR),bpsk(snr,ER)));
data=double(xor(bpsk(snr,DR),ER));
%if biterr(data,X1)>=1
%    fer=1;
%else
%    fer=0;
%end
ber=biterr(data,X1)/data_bits;
end

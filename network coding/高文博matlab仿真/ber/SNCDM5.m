function [ber] = SNCDM5(snr)
data_bits=100;
X1=randi([0,1],1,data_bits);
X2=randi([0,1],1,data_bits);
Y3=randi([0,1],1,data_bits);
Y2=randi([0,1],1,data_bits);
AR=X1;
BR=bpsk(snr,AR);
CR=bpsk(snr,BR);
ER=Y2;
DR=bpsk(snr,ER);
DR=double(xor(bpsk(snr,CR),DR));
data=double(xor(bpsk(snr,DR),ER));

%if biterr(data,X1)>=1
%    fer=1;
%else
%    fer=0;
%end
ber=biterr(data,X1)/data_bits;
end
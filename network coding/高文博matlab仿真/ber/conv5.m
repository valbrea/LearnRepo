function [ output ] = conv5(snr)
X1=randi([0,1],1,100);
X2=bpsk(snr,X1);
X3=bpsk(snr,X2);
X4=bpsk(snr,X3);
X5=bpsk(snr,X4);
if biterr(X1,X5)>=1
    output=1;
else
    output=0;
end
end
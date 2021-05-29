function[ output ] = bpsk( snr , input1)
x=pskmod(input1,2);
R=raylrnd(0.5,1,length(input1));
xR=x.*R;
yRn=awgn(xR,snr,'measured');
output=pskdemod(yRn,2); 
end

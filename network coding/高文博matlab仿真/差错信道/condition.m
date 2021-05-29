function [ trans ] = condition()
SNR=24;
SNR1=10^(SNR / 10);
data_bits=100;
BPSK=0.5 * (1 - sqrt(SNR1/ (SNR1 + 1)));
lam=1-(1-BPSK)^data_bits;
A=unifrnd(0,1);
if A<((1-lam)^2)%Õý³£ 
    trans=0;  
elseif (A>(1-lam)^2)&&(A<lam) %ÓÒ´«Ê§°Ü
   trans=1;    
elseif (A>lam)&&(A<1-(1-lam)^2) %×ó´«Ê§°Ü
    trans=2; 
else %¾ùÊ§°Ü
    trans=3;
%trans=0;
end


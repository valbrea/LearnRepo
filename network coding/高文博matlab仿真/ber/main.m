SNR=5:5:40;
ber=zeros(1,length(SNR));
ber1=zeros(1,length(SNR));
ber2=zeros(1,length(SNR));
ber3=zeros(1,length(SNR));

for i=1:length(SNR)
    ber(i)=ber5(SNR(i));
    ber1(i)=0.5*(1-1/sqrt(1+10*10^(-SNR(i)/10)));
    ber2(i)=0.5*(1-1/sqrt(1+6*10^(-SNR(i)/10)));
    %ber3(i)=test(SNR(i));
end
semilogy(SNR,ber,'bs-');
hold on;
semilogy(SNR,ber1,'b*-');
hold on;
semilogy(SNR,ber2,'r*-');
hold on;
semilogy(SNR,ber3,':r');
axis([5 40 10^-4 1]);
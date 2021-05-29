function[ output ] = test3( snr )
input1=randi([0,1],1,100);
input=2*input1-1;
n = 1/sqrt(2)*(randn(1,length(input)) + 1i*randn(1,length(input))); % white gaussian noise, 0dB variance 
h = 1/sqrt(2)*(randn(1,length(input)) + 1i*randn(1,length(input))); % Rayleigh channel
% Channel and noise Noise addition
y = h.*input + 10^(-snr/20)*n; 
% equalization
yHat = y./h;
% receiver - hard decision decoding
output = double(real(yHat)>0);

end


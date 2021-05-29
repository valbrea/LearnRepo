function [output] =oneway(data,SNR)
r=BPSK(SNR,data);
if isequal(r,data)
    output=1;
else
    output=0;
end
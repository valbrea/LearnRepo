function [output] = twoway(data,SNR)
r=BPSK(SNR,data);
l=BPSK(SNR,data);
if isequal(r,data)&&isequal(l,data)
    output=1;
elseif ~isequal(r,data)&&isequal(l,data)
    output=2;
elseif isequal(r,data)&&~isequal(l,data)
    output=3;
else
    output=0;
end
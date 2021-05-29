function [ trans ] = TRANSL(SNR,data )
data=double(data);
L=BPSK(SNR,data);
if isequal(L,data)
    trans=0;
else
    trans=2;
end
end
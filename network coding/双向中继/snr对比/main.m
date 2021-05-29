function [ output ] = main( SNR )
output=0;
for i=1:1000
        output=output+NO_MDFNC5(SNR);   
end
output=output/1000;
end

 
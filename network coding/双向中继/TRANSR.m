function [trans] = TRANSR(SNR, data)
    data = double(data);
    R = BPSK(SNR, data);

    if isequal(R, data)
        trans = 0;
    else
        trans = 1;
    end

end

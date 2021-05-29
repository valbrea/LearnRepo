function [trans, L, R] = TRANS2(SNR, data)
    data = double(data);
    R = BPSK(SNR, data);
    L = BPSK(SNR, data);

    if isequal(R, data) && isequal(L, data)%正确传输
        trans = 0;
    elseif ~isequal(R, data) && isequal(L, data)%右传失败
        trans = 1;
    elseif isequal(R, data) &&~isequal(L, data)%左传失败
        trans = 2;
    else %均失败
        trans = 3;
    end

end

function [flag, left, right] = TransBi(SNR, pkg)
left = BPSK(SNR, pkg);
right = BPSK(SNR, pkg);
if isequal(left, pkg) && isequal(right, pkg) % 正确传输
    flag = 0;
elseif isequal(left, pkg) && ~isequal(right, pkg) % 右传失败
    flag = 1;
elseif ~isequal(left, pkg) && isequal(right, pkg) % 左传失败
    flag = 2;
else % 均失败
    flag = 3;
end
end

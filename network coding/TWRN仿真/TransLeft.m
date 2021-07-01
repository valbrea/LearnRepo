function [flag, left] = TransLeft(SNR, pkg)
left = BPSK(SNR, pkg);
if isequal(left, pkg)
    % 左传成功
    flag = 0;
else
    % 左传失败
    flag = 2;
end
end

function [flag, right] = TransRight(SNR, pkg)
right = BPSK(SNR, pkg);
if isequal(right, pkg)
    % 右传成功
    flag = 0;
else
    % 右传失败
    flag = 1;
end
end

function [flag] = ACK(pkg1, pkg2)
if isequal(pkg1, pkg2)
    flag = 1; % 传输成功
else
    flag = 0; % 失败
end
end

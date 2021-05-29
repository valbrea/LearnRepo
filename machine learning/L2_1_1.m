clear all;
close all;
L = 1000;
V = randn(1,L) * (0.2)^0.5;
uu = randn(1,L);
yy = zeros(1,L);
for ii = 3:L
    yy(ii) = uu(ii-1) + 0.5 * uu(ii-2) + V(ii)-1.5 * yy(ii-1)-0.7 * yy(ii-2);
end

A=[(uu(2:L-1))',(uu(1:L-2))',(-yy(2:L-1))',(-yy(1:L-2))'];
b=yy(3:end)';
x=pinv(A) * b;
figure, plot(uu);
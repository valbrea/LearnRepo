clear all;
close all;
L = 1000;
p = 4;
V = randn(1,L) * (0.2)^0.5;
wo = randn(p,1);
uu = randn(p,L);
dd = wo'*uu + V;

A = uu';
b = dd';%≤ª”√ºıV, V «‘Î…˘
w1 = pinv(A) * b;

norm(w1 - wo);
w = randn(p,1);
mu = 0.01;
for ii = 1:L
    ee = dd(ii) - w'* uu(:,ii);
    w = w + mu * ee * uu(:,ii);
    Err(ii) = norm(w-wo);
end
figure,plot(Err);


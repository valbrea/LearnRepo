%% karlman filter
clear all; close all;
L = 1000;
p = 1;
q = 1;
A = 0.9 * eye(p);
C = 1;
w = randn(p,L) * 0.1;
v = randn(q,L) * 0.2;
Q = w * w' / L;
R = v * v' / L;
xx(1) = randn;
xe(1) = 0;
Pk = eye(p) * 0.1;

for ii = 2 : L
    xx(ii) = A * xx(ii-1) + w(ii-1);
    yy(ii) = C * xx(ii) + v(ii);
    Pke = A * Pk * A' + Q;
    H = Pke * C' * inv(C * Pke * C' + R);
    xe(ii) = A * xe(ii-1) + H * (yy(ii) - C * A * xe(ii-1));
    Pk = Pke - H * C * Pke;
end

figure, hold on;
plot(xx,'.');plot(yy,'r');

figure, plot(yy - xx);

figure, hold on;
plot(xx,'.');plot(xe,'r');

figure, plot(abs(xx-xe));
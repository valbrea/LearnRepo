clear all; close all;
x = -25 : 0.1 :25;
a1 = 1; % a代表σ
a2 = 2;
a3 = 3;
a4 = 5;

y1 = exp( - (x - 1).^2 / 2 /a1^2); % 以1为中心
y2 = exp( - (x + 3).^2 / 2 /a2^2); % 以-3为中心
y3 = exp( - x.^2 / 2 /a3^2);
y4 = exp( - x.^2 / 2 /a4^2);

figure,hold on;
plot(x,y1,'r');
plot(x,y2,'g');
plot(x,y3,'b');
plot(x,y4,'k');

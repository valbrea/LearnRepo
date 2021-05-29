clear all, close all;
x = 0:0.1:100;
%% Part 1
y1 = gaussmf(x, [10, 20]);
y2 = gaussmf(x, [10, 35]);
y3 = gaussmf(x, [10, 50]);
y4 = gaussmf(x, [10, 65]);
y5 = gaussmf(x, [10, 80]);

ym = y1 + y2 + y3 + y4 + y5;

yy1 = y1./ym;
yy2 = y2./ym;
yy3 = y3./ym;
yy4 = y4./ym;
yy5 = y5./ym;

figure, hold on;
plot(x, yy1);
plot(x, yy2);
plot(x, yy3);
plot(x, yy4);
plot(x, yy5);
%% Part 2
y1 = gaussmf(x, [10, 20]);
y2 = gaussmf(x, [10, 25]);
y3 = gaussmf(x, [10, 50]);
y4 = gaussmf(x, [10, 62]);
y5 = gaussmf(x, [10, 80]);

ym = y1 + y2 + y3 + y4 + y5;

yy1 = y1./ym;
yy2 = y2./ym;
yy3 = y3./ym;
yy4 = y4./ym;
yy5 = y5./ym;

figure, hold on;
plot(x, yy1);
plot(x, yy2);
plot(x, yy3);
plot(x, yy4);
plot(x, yy5);
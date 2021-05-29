clear all; close all;

x = 1 : 0.1 : 5;
y = sigmf(x,[2, 2.5]);

figure;
plot(x,y);
title('MF ¦Ì_T(x) for ¡°temperature is low¡±')
xticks([1 2 3 4 5])
xticklabels({'x_1(hot)','x_2(warm)','x_3(cool)','x_4(chilly)','x_5(cold)'})

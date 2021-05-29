clear all; close all;
xr = 100 * rand(1, 100);
yr = 100 * rand(1, 100);
 
cntx = sum(xr)/100;
cnty = sum(yr)/100;

D = sqrt((yr - cnty).^2 + (xr - cntx).^2);
D = D / max(D) * 10;

x1 = D; % 与簇中心距离
x2 = rand(1,100) * 10; % 电量[1,10]随机数
x3 = rand(1,100) * 10; % 移动性[1,10]随机数
 
clear var;close all;
x = 0:0.1:10;
%% gaussion MF
y = gaussmf(x,[2, 6]);
figure;
plot(x,y,'r');
%F = 0.1315 /1 + 0.8825 /4 + 1 /5 + 0.8825/6 + 0.1315 /9
%% triangle MF
y2 = trimf(x,[1, 4, 9]);
figure;
plot(x,y2,'g');
%% sigmoidal MF
y3 = sigmf(x,[-3, 4]);
figure;
plot(x,y3,'b');
%% trapezoidal MF
y4 = trapmf(x,[2, 5, 7, 9]);
figure;
plot(x,y4,'k');
%% generalized bell MF
y5 = gbellmf(x,[2, -5, 6]);
figure;
plot(x,y5,'c');
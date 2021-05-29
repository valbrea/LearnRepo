clear all; close all;

x = 0:0.1:10;
%% gaussion MF
% 1)	Gaussian MF with m = 6, ¦Ò = 2
y = gaussmf(x,[2, 6]);
figure;
plot(x,y,'r');
title('Gaussian MF with m = 6, ¦Ò = 2');

%% triangle MF
% 2)	Triangular MF with a = 1, b = 4, c = 9 
y2 = trimf(x,[1, 4, 9]);
figure;
plot(x,y2,'g');
title('Triangular MF with a = 1, b = 4, c = 9');

%% sigmoidal MF
% 3)	Sigmoidal MF with a = -3, c = 4
y3 = sigmf(x,[-3, 4]);
figure;
plot(x,y3,'b');
title('Sigmoidal MF with a = -3, c = 4');

%% trapezoidal MF
% 4)	Trapzoidal MF with a = 2, b = 5, c = 7, d = 9 
y4 = trapmf(x,[2, 5, 7, 9]);
figure;
plot(x,y4,'k');
title('Trapzoidal MF with a = 2, b = 5, c = 7, d = 9');

%% generalized bell MF
% 5)	Generalized bell MF with a =1, b = 2, c = 5. 
y5 = gbellmf(x,[1, 2, 5]);
figure; hold on;
plot(x,y5,'c');
title('Generalized bell MF');
% Change a = 3, keep b = 2, c = 5, plot another gbell MF.
y6 = gbellmf(x,[3, 2, 5]);
plot(x,y6,'m');
legend('a = 1, b = 2, c = 5','a = 3, b = 2, c = 5');

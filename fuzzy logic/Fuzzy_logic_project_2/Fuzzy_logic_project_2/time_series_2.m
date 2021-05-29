%series tao=40
tao=40;
s_t = rand(1,tao+1); %随机产生tao+1个数据，后面用于作为初始值
n = 2000;
f_s_n = []; %定义为s(n)对时间t的导数
s_n = []; %定义时间序列s(n)
s_n(1:tao+1) = s_t; %用初始值来产生平稳型时间数列用于接下来的预测
s = 1; %记录第几个s(n)的导数
for i = tao+1:n %开始预测
    f_s_n(s) = 0.2*s_n(i-tao) / (1+s_n(i-tao)^10) - 0.1*s_n(i);
    s_n(i+1) = s_n(i) + f_s_n(s);   
    s = s+1;
end
figure;
plot(1000:1500,s_n(1000:1500));
%axis([1000,1500,0.1,1.6])
title('time series with tao=40');

figure,
plot(s_n(1000:1500),s_n(1000-tao:1500-tao));
title('phase for tao=40');
xlabel('s(t)');ylabel('s(t-d)');

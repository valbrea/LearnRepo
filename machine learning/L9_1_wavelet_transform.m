clear all; close all;
load scddvbrk;
x = scddvbrk;
level = 2;
[c,I] = wavedec(x,level,' db4');
[d1,d2] = detcoef(c,I,1:level);
subplot(311),plot(x),xlim([400 600])
subplot(312),d1up(1:2:1008)=d1;plot(d1up);ylabel('d1 '),xlim([400 600])
subplot(313),d2up(1:4:1020)= d2;plot(d2up);ylabel('d2'),xlim([400 600])
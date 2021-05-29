x0=rand(1,100)*100;
y0=rand(1,100)*100;
 
x_0=sum(x0)/100;
y_0=sum(y0)/100;
%plot(x_0,y_0,'r.')
range=((y0-y_0).^2+(x0-x_0).^2).^(1/2);
range=range/max(range)*10;
x1=range;
x2=rand(1,100)*10;
x3=rand(1,100)*10;
function [ output ] = Tsend( )
A=unifrnd(0,1);
if A<0.8
    output=randi([0,1],1,8472);
else
    output=zeros(1,8472);
end


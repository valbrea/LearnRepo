
base=[0;1];
period=size(base,1);
num=4;
all=period^num;
final=[];
for i= 1:num
    column=kron(base,ones(period^(i-1),1));
    column=repmat(column,all/(size(base,1)*period^(i-1)),1);
    final=[final,column];
end
final1 = fliplr(final);
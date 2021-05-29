function [ throughput ] = amatlab ( time )

H_p=0.7;
T_p=0.7;

     
N=4; %中继节点个数


TA=N+1;
Tb=2*N+1;
switch mod(N,3)
    case 0
        Tr=1;
    case 1
        Tr=2; 
    case 2
        Tr=0;
end
TB=Tb+Tr;

if 0<=time&&time<N
    throughput=0;
elseif N<=time&&time<TB-1 
    throughput=(1+H_p*fix((time-TA+1)/3))/(time+1);
else
    throughput=(H_p*(1+fix((time-TA+1)/3))+T_p*(1+fix((time-TB+1)/3)))/(time+1);
end

end


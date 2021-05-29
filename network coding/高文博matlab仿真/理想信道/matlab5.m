function [ throughput ] = matlab5( time )
     
N=3; %中继节点个数


TA=N+1;
TB=2*N+N+mod(N+1,3);


if 0<=time&&time<N
    throughput=0;
elseif time==N
    throughput=1/(time+1);
elseif N<=time&&time<TB-1 
    throughput=(1+fix((time-TA+1)/3))/(time+1);
elseif time==TB-1 
    throughput=(1+(1+fix((time-TA+1)/3)))/(time+1);
else
    throughput=((1+fix((time-TA+1)/3))+(1+fix((time-TB+1)/3)))/(time+1);
end

end
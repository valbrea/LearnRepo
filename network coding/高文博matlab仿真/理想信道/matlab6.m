function [ throughput ] = matlab6 ( time )
     
N=4; %中继节点个数



Tb=mod(N+1,3)+2*N;


if 0<=time&&time<N
    throughput=0;
elseif N<=time&&time<Tb-1 
    throughput=(1+fix((time-N)/3))/(time+1);
else
    throughput=(2+fix((time-N)/3)+fix((time-Tb)/3))/(time+1);
end

end


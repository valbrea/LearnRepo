clear; close all;
load woman;
%X=rand(8);
[M,N]=size(X);
[f1,f2,l1,h1]=wfilters('db2');
X1=zeros(M+4,N+4);
X1(3:M+2,3:N+2)=X;
%X1(2,2)=X(1,1);X1(2,N+3)=X(1,N);X1(M+3,N+3)=X(M,N);X1(M+3,2)=X(M,1);
for i=2:M+1
    X1(i+1,1)=X(i-1,2);
    X1(i+1,2)=X(i-1,1);
    X1(i+1,N+3)=X(i-1,N);
    X1(i+1,N+4)=X(i-1,N-1);
end
for j=2:N+1
    X1(1,j+1)=X(2,j-1);
    X1(2,j+1)=X(1,j-1);
    X1(M+3,j+1)=X(M,j-1);
    X1(M+4,j+1)=X(M-1,j-1);
end
X1(1,1:2)=X1(4,1:2);X1(2,1:2)=X1(3,1:2);
X1(1,M+3:M+4)=X1(4,M+3:M+4);X1(2,M+3:M+4)=X1(3,M+3:M+4);
X1(M+3:M+4,1)=X1(M+3:M+4,4);X1(M+3:M+4,2)=X1(M+3:M+4,3);
X1(M+3:M+4,M+3)=X1(M+3:M+4,M+2);X1(M+3:M+4,M+4)=X1(M+3:M+4,M+1);
[c,s]=wavedec2(X,1,'db2');
cA=appcoef2(c,s,'db2',1);
LH1=detcoef2('h',c,s,1);
HL1=detcoef2('v',c,s,1);
HH1=detcoef2('d',c,s,1);
%%%% extract the LL parameter
K=round(M/2+1);
L=round(N/2+1);
LL=zeros(K,L);LH=LL;
HL=LL; HH=LL;
for i=2:K+1
    for j=2:L+1
        for k=2*i-3:2*i
            for l=2*j-3:2*j
                m=1+2*i-k;
                n=1+2*j-l;
                LL(i-1,j-1)=LL(i-1,j-1)+f1(m)*f1(n)*X1(k,l);
                LH(i-1,j-1)=LH(i-1,j-1)+f2(m)*f1(n)*X1(k,l);
                HL(i-1,j-1)=HL(i-1,j-1)+f1(m)*f2(n)*X1(k,l);
                HH(i-1,j-1)=HH(i-1,j-1)+f2(m)*f2(n)*X1(k,l);
            end
        end
    end
end
%%%%%%% end of extraction %%%%%%%%%%
X2=zeros(M,N);
%%%%%%% reconstruction 
for i=1:M
    for j=1:N
        for k=ceil(i/2):floor(i/2+3/2)
            for l=ceil(j/2):floor(j/2+3/2)
                m=2*k-i+1;
                n=2*l-j+1;
                X2(i,j)=X2(i,j)+f1(m)*f1(n)*LL(k,l)+f2(m)*f1(n)*LH(k,l)+f1(m)*f2(n)*HL(k,l)+f2(m)*f2(n)*HH(k,l);
            end
        end
    end
end
[norm(cA-LL)  norm(LH1-LH) norm(HL1-HL) norm(HH1-HH)]
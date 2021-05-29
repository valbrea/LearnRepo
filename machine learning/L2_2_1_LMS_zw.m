%%
%LMS算法的改进:归一化LMS（NLMS算法）和解相关LMS
L=2000;
p=5;
wo=randn(p,1);
vv=randn(1,L)*0.5;
uu=randn(p,L);
dd=wo'*uu+vv;%5个未知数，2000个方程
%协方差矩阵和互相关矩阵，维纳滤波
w=inv(uu*uu')*(uu*dd')
Error=norm(w-wo)
%LMS
w_lms=zeros(p,1);
mu_lms=0.01;%步长
for ii=1:L
    Err_lms(ii)=norm(w_lms-wo);%PI，性能指标
    en=dd(ii)-w_lms'*uu(:,ii);
    w_lms=w_lms+mu_lms*en*uu(:,ii);
end

%LMS2
w_lms2=zeros(p,1);
mu_lms2=0.1;%步长
for ii=1:L
    Err_lms2(ii)=norm(w_lms2-wo);
    en2=dd(ii)-w_lms2'*uu(:,ii);
    w_lms2=w_lms2+mu_lms2*en2*uu(:,ii);
end

%LMS3，变步长
w_lms3=zeros(p,1);
mu_lms=0.1;%步长
for ii=1:L
    Err_lms3(ii)=norm(w_lms3-wo);
    en2=dd(ii)-w_lms3'*uu(:,ii);
    mu(ii)=mu_lms/round(ii/100+1);%是变步长,每100次减小一次，
    w_lms3=w_lms3+mu(ii)*en2*uu(:,ii);
end

%NLMS
w_lms4=zeros(p,1);
mu_lms=0.1;%步长
for ii=1:L
    Err_lms4(ii)=norm(w_lms4-wo);
    en2=dd(ii)-w_lms4'*uu(:,ii);
    w_lms4=w_lms4+mu_lms*en2*uu(:,ii)/(uu(:,ii)'*uu(:,ii));
end

%解相关LMS，LMS5
w_lms5=zeros(p,1);
mu_lms=0.1;%步长
Err_lms5=norm(w_lms5-wo)
for ii=2:L
    Err_lms5(ii)=norm(w_lms5-wo);
    en2=dd(ii)-w_lms5'*uu(:,ii);
    alpha=(uu(:,ii-1)'*uu(:,ii))/(uu(:,ii-1)'*uu(:,ii-1));
    vn=uu(:,ii)-alpha*uu(:,ii-1);
    w_lms5=w_lms5+mu_lms*en2*vn;
end

figure 
plot(Err_lms,'r');
hold on
plot(Err_lms2,'g');
plot(Err_lms3,'b');
plot(Err_lms4,'k');
plot(Err_lms5,'m');
legend('LMS1步长0.01','LMS2步长0.1','LMS变步长','NLMS步长0.1','解相关LMS步长0.1')
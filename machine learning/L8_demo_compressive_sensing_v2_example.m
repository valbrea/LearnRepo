clc; 
close all;
 clear all;
 
 tic;
 
%  im=imread('lena.bmp');
%  im=double(im);
 load woman;
%  X=X(1:2:end,1:2:end);
 im=X;
  im=double(im);
 [m,n]=size(im);
 im2=zeros(m,n);
%  bm=8;bn=8;
 bm=4;bn=4;
 p=1;
 d=bm*bn;
 N=round(d*p);
 N=16;
 bx=ceil(m/bm);
 by=ceil(n/bn);
 imc=zeros(bx*bm,by*bn);
 
 for ii=1:bx*bm
     for jj=1:by*bn
         if ii<=m && jj<=n
             imc(ii,jj)=im(ii,jj);
         else
             imc(ii,jj)=0;
         end
     end
 end
 
 
 for x=1:bx
     for y=1:by
         b=imc((1+(x-1)*bm):(x*bm),(1+(y-1)*bn):(y*bn));
         xin=reshape(b,d,1);
         xin=double(xin);
         
         A=dctmtx(d);
         Phi=randn(N,d);
         T=Phi*inv(A);  %%传感矩阵
         T=Phi;%%modification 1/3
         s=Phi*xin;     %% 观测值
         s=Phi*inv(A)*xin;%%modification 2/3
         
         hat_y=zeros(1,d);
         Aug_t=[];
         aug_y=[];
         pos_array=[];
         r_n=s;
         times=1;
         
         while norm(r_n)>0.01
             for col=1:d
                 product(col)=abs(T(:,col)'*r_n);
             end
             [val,pos]=max(product);
             Aug_t=[Aug_t,T(:,pos)];
             T(:,pos)=zeros(N,1);
             aug_y=pinv(Aug_t'*Aug_t)*Aug_t'*s;
             r_n=s-Aug_t*aug_y;
             pos_array(times)=pos;
             times=times+1;
         end
             
             
          hat_y(pos_array)=aug_y;
          hat_x=hat_y;
          hat_x2=inv(A)*hat_x';
             hat_x2=A*hat_x';%%modification 3/3
          b2=reshape(hat_x2,bm,bn);
             
          imc2((1+(x-1)*bm):(x*bm), (1+(y-1)*bn):(y*bn))=b2;
         
     end
 end
  toc;
 imc2=uint8(imc2);
 im2=imc2(1:m,1:n);
 im2=double(im2);
 mse=mean(mean(abs(im-im2).^2));
 

 
 figure(1);
%  imagesc(im2);
 imshow(im2,[]);
 figure,plot(abs(hat_y),'.')
 
 
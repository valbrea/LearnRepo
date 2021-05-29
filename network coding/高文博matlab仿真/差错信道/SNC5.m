function [throughput] = SNC5(slot)
data_bits=8472;
X_1=randi([0,1],1,data_bits);
X_2=randi([0,1],1,data_bits);
Y_1=randi([0,1],1,data_bits);
Y_2=randi([0,1],1,data_bits);
Y_3=randi([0,1],1,data_bits);
R_2=Y_1;
R_3=xor(X_2,Y_1);
R_4=xor(X_1,X_2);
R_5=xor(X_2,Y_2);
R_6=xor(Y_2,Y_3);


RT_1=0;
RT_2=0;
RT_3=0;
RT_4=0;
RT_5=0;
RT_6=0;
RT_7=0;
RT_8=0;

RR_1=1;
RR_2=1;
LR_2=0;
RR_3=0;
LR_3=0;
RR_4=0;
LR_4=1;
RR_5=1;
LR_5=1;
RR_6=1;
LR_6=0;
RR_7=0;
LR_7=0;
LR_8=1;

output=0;
prate=11*10^6; 
T=data_bits/prate; 

tbegin=zeros(1,slot);
tend=zeros(1,slot);

tbegin(1)=1;
tbegin(2)=5;
i=3;
j=1;

for time=1:slot %仿真时间
    type=mod(time,4); %将过程分为四个阶段
    switch type
        case 1 %节点1 节点5
            if RT_1==1||RR_1==1 %节点1
                RT_1=condition2();
                R_1=randi([0,1],1,data_bits);
                if RT_1==0
                    tbegin(i)=time+8;
                    i=i+1;
                    R_2=xor(R_2,R_1);
                    LR_2=LR_2+1;
                    RR_1=RR_1-1;
                end
            end
            
             if RT_5==1 %节点5
                RT_5=condition2();
                if RT_5==0
                    R_6=xor(R_5,R_6);
                    RR_5=RR_5-1;
                    LR_6=LR_6+1;
                else
                    RT_5=1;
                end
            elseif RT_5==2
                RT_5=condition2();
                if RT_5==0
                    R_4=xor(R_4,R_5);
                    LR_5=LR_5-1;
                    RR_4=RR_4+1;
                else
                    RT_5=2;
                end
            elseif (RT_5==3)||(RR_5==1&&LR_5==1)
                RT_5=condition();
                if RT_5==0
                    R_6=xor(R_5,R_6);
                    R_4=xor(R_5,R_4);
                    LR_5=LR_5-1;
                    RR_5=RR_5-1;
                    LR_6=LR_6+1;
                    RR_4=RR_4+1;
                elseif RT_5==1
                    R_4=xor(R_5,R_4);
                    LR_5=LR_5-1;
                    RR_4=RR_4+1;
                elseif RT_5==2
                    R_6=xor(R_5,R_6);
                    RR_5=RR_5-1;
                    LR_6=LR_6+1;
                end
             end
             
        case 2 % 节点4 节点8
            if RT_4==1 %节点4 
                RT_4=condition2();
                if RT_4==0
                    R_5=xor(R_4,R_5);
                    RR_4=RR_4-1;
                    LR_5=LR_5+1;
                else
                    RT_4=1;
                end
            elseif RT_4==2
                RT_4=condition2();
                if RT_4==0
                    R_3=xor(R_4,R_3);
                    LR_4=LR_4-1;
                    RR_3=RR_3+1;
                else
                    RT_4=2;
                end
            elseif (RT_4==3)||(RR_4==1&&LR_4==1)
                RT_4=condition();
                if RT_4==0
                    R_5=xor(R_4,R_5);
                    R_3=xor(R_3,R_4);
                    LR_4=LR_4-1;
                    RR_4=RR_4-1;
                    LR_5=LR_5+1;
                    RR_3=RR_3+1;
                elseif RT_4==1
                    R_3=xor(R_3,R_4);
                    LR_4=LR_4-1;
                    RR_3=RR_3+1;
                elseif RT_4==2
                    R_5=xor(R_5,R_4);
                    RR_4=RR_4-1;
                    LR_5=LR_5+1;
                end
            end 
                       
        case 3
            if RT_2==1 %节点2 
                RT_2=condition2();
                if RT_2==0
                    R_3=xor(R_2,R_3);
                    RR_2=RR_2-1;
                    LR_3=LR_3+1;
                else
                    RT_2=1;
                end
            elseif RT_2==2
                RT_2=condition2();
                if RT_2==0
                    output=output+1;
                    LR_2=LR_2-1;
                    RR_1=RR_1+1;
                else
                    RT_2=2;
                end
            elseif (RT_2==3)||(RR_2==1&&LR_2==1)
                RT_2=condition();
                if RT_2==0
                    output=output+1;
                    R_3=xor(R_3,R_2);
                    LR_2=LR_2-1;
                    RR_2=RR_2-1;
                    LR_3=LR_3+1;
                    RR_1=RR_1+1;
                elseif RT_2==1
                    output=output+1;
                    LR_2=LR_2-1;
                    RR_1=RR_1+1;
                elseif RT_2==2
                    R_3=xor(R_2,R_3);
                    RR_2=RR_2-1;
                    LR_3=LR_3+1;
                end
            end
            
            if RT_6==1 %节点6 
                RT_6=condition2();
                if RT_6==0
                    output=output+1;
                    tend(j)=time+8;
                    j=j+1;
                    RR_6=RR_6-1;
                    LR_7=LR_7+1;
                else
                    RT_6=1;
                end
            elseif RT_6==2
                RT_6=condition2();
                if RT_6==0
                    R_5=xor(R_6,R_5);
                    LR_6=LR_6-1;
                    RR_5=RR_5+1;
                else
                    RT_6=2;
                end
            elseif (RT_6==3)||(RR_6==1&&LR_6==1)
                RT_6=condition();
                if RT_6==0
                    output=output+1;
                    tend(j)=time+8;
                    j=j+1;
                    R_5=xor(R_5,R_6);
                    LR_6=LR_6-1;
                    RR_6=RR_6-1;
                    LR_7=LR_7+1;
                    RR_5=RR_5+1;
                elseif RT_6==1
                    R_5=xor(R_5,R_6);
                    LR_6=LR_6-1;
                    RR_5=RR_5+1;
                elseif RT_6==2
                    output=output+1;
                    tend(j)=time+8;
                    j=j+1;
                    RR_6=RR_6-1;
                    LR_7=LR_7+1;
                end
            end  
            
        case 0
             if RT_3==1 %节点3 
                RT_3=condition2();
                if RT_3==0
                    R_4=xor(R_4,R_3);
                    RR_3=RR_3-1;
                    LR_4=LR_4+1;
                else
                    RT_3=1;
                end
            elseif RT_3==2
                RT_3=condition2();
                if RT_3==0
                    R_2=xor(R_2,R_3);
                    LR_3=LR_3-1;
                    RR_2=RR_2+1;
                else
                    RT_3=2;
                end
            elseif (RT_3==3)||(RR_3==1&&LR_3==1)
                RT_3=condition();
                if RT_3==0
                    R_4=xor(R_3,R_4);
                    R_2=xor(R_3,R_2);
                    LR_3=LR_3-1;
                    RR_3=RR_3-1;
                    LR_4=LR_4+1;
                    RR_2=RR_2+1;
                elseif RT_3==1
                    R_2=xor(R_3,R_2);
                    LR_3=LR_3-1;
                    RR_2=RR_2+1;
                elseif RT_3==2
                    R_4=xor(R_4,R_3);
                    RR_3=RR_3-1;
                    LR_4=LR_4+1;
                end
             end
             
             
             if RT_7==1||LR_7==1 %节点7
                RT_7=condition2();
                R_7=randi([0,1],1,data_bits);
                if RT_7==0
                    R_6=xor(R_6,R_7);
                    LR_7=LR_7-1;
                    RR_6=RR_6+1;
                end
            end
  
    end
end
throughput=output*data_bits/((time+8)*T);
shiyan=tend-tbegin;
end
function [throughput] = SNC4(SNR, slot)
data_bits=8472;
%初始化
X_1=randi([0,1],1,data_bits);
X_2=randi([0,1],1,data_bits);
Y_1=randi([0,1],1,data_bits);
Y_2=randi([0,1],1,data_bits);
R_2=xor(X_2,Y_1);
R_3=xor(X_1,Y_1);
R_4=xor(X_1,Y_2);
R_5=X_1;

RT_1=0;
RT_2=0;
RT_3=0;
RT_4=0;
RT_5=0;
RT_6=0;

RR_1=0;
RR_2=1;
LR_2=1;
LR_6=1;
RR_3=1;
LR_3=0;
RR_4=0;
LR_4=0;
LR_5=1;
RR_5=0;

throughput = zeros(1, slot);
output=0;
prate=11*10^6; 
T=data_bits/prate; 
% slot=1000;

tbegin=[0 1 5];
tend=0;

for time=1:slot %仿真时间
    type=mod(time,4); %将过程分为五个阶段
    switch type
        case 1
            if RT_2==1 %节点2 
                RT_2=TRANSR(SNR,R_2);
                if RT_2==0
                    R_3=XOR(R_2,R_3);
                    RR_2=RR_2-1;
                    LR_3=LR_3+1;
                end
            elseif RT_2==2
                RT_2=TRANSL(SNR,R_2);
                if RT_2==0
                    output=output+1;
                    LR_2=LR_2-1;
                    RR_1=RR_1+1;
                end
            elseif (RT_2==3)||(RR_2==1&&LR_2==1)
                RT_2=TRANSR(SNR,R_2);
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
            
            if RT_6==1||LR_6==1 %节点6
                R_6=randi([0,1],1,data_bits);
                RT_6=TRANSR(SNR,R_6);
                if RT_6==0
                    R_5=xor(R_5,R_6);
                    LR_6=LR_6-1;
                    RR_5=RR_5+1;
                end
            end
            
        case 2
            if RT_1==1||RR_1==1 %节点1
                R_1=randi([0,1],1,data_bits);
                RT_1=TRANSR(SNR,R_1);             
                if RT_1==0
                    tbegin=[tbegin,time+8];
                    R_2=xor(R_2,R_1);
                    LR_2=LR_2+1;
                    RR_1=RR_1-1;
                end
            end
            
            if RT_5==1 %节点5
                RT_5=TRANSR(SNR,R_5);
                if RT_5==0
                    output=output+1;
                    tend=[tend,time+8];
                    RR_5=RR_5-1;
                    LR_6=LR_6+1;
                end
            elseif RT_5==2
                RT_5=TRANSL(SNR,R_5);
                if RT_5==0
                    R_4=xor(R_4,R_5);
                    LR_5=LR_5-1;
                    RR_4=RR_4+1;
                else
                    RT_5=2;
                end
            elseif (RT_5==3)||(RR_5==1&&LR_5==1)
                RT_5=TRANS2(SNR,R_5);
                if RT_5==0
                    output=output+1;
                    tend=[tend,time+8];
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
                    output=output+1;
                    tend=[tend,time+8];
                    RR_5=RR_5-1;
                    LR_6=LR_6+1;
                end
             end
            
        case 3
             if RT_3==1 %节点3 
                RT_3=TRANSR(SNR,R_3);
                if RT_3==0
                    R_4=xor(R_4,R_3);
                    RR_3=RR_3-1;
                    LR_4=LR_4+1;
                else
                    RT_3=1;
                end
            elseif RT_3==2
                RT_3=TRANSL(SNR,R_3);
                if RT_3==0
                    R_2=xor(R_2,R_3);
                    LR_3=LR_3-1;
                    RR_2=RR_2+1;
                else
                    RT_3=2;
                end
            elseif (RT_3==3)||(RR_3==1&&LR_3==1)
                RT_3=TRANS2(SNR,R_3);
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
            
        case 0
            if RT_4==1 %节点4 
                RT_4=TRANSR(SNR,R_4);
                if RT_4==0
                    R_5=xor(R_4,R_5);
                    RR_4=RR_4-1;
                    LR_5=LR_5+1;
                else
                    RT_4=1;
                end
            elseif RT_4==2
                RT_4=TRANSL(SNR,R_4);
                if RT_4==0
                    R_3=xor(R_4,R_3);
                    LR_4=LR_4-1;
                    RR_3=RR_3+1;
                else
                    RT_4=2;
                end
            elseif (RT_4==3)||(RR_4==1&&LR_4==1)
                RT_4=TRANS2(SNR,R_4);
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
    end
    throughput(time) = output/(time+8);
end
number=length(tend);
tbegin=tbegin(:,2:number);
tend=tend(:,2:number);
delay=tend-tbegin;
delay=mean(delay(:));

% figure;
% plot(throughput, 'r');
% xlabel('timeslot'), ylabel('throughput');
end

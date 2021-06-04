function [throughput] = DFNC4(SNR, slot)
data_bits=8472;
R_1=randi([0,1],1,data_bits);
R_2=zeros(1,data_bits);
R_6=randi([0,1],1,data_bits);
R_5=R_6;
R_3=R_1;
R_4=XOR(R_5,R_1);

RR_1=1;
LR_2=0;
RR_2=0;
LR_3=0;
RR_3=0;
RR_4=1;
LR_4=1;
LR_5=0;
RR_5=0;
LR_6=0;

RT_1=0;
RT_2=0;
LRT_3=0;
RRT_3=0;
RT_4=0;
LRT_5=0;
RRT_5=0;
RT_6=0;

throughput = zeros(1, slot);
output=0;
prate=11*10^6; 
T=data_bits/prate; 

% slot=1000;

tbegin=[0,1];
tend=0;

for time=1:slot %仿真时间
    type=mod(time,5); %将过程分为五个阶段
    switch type
        case 1
            if RR_1==1||RT_1==1 % 节点1 右传
                R_1=randi([0,1],1,data_bits);
                RT_1=TRANSR(SNR,R_1);
                if RT_1==0
                    tbegin=[tbegin,time+4];
                    R_2=XOR(R_1,R_2);
                    LR_2=LR_2+1;
                    RR_1=RR_1-1;
                end
            end
            
            if RT_4==2 % 节点4 双向
                RT_4=TRANSL(SNR,R_4);
                if RT_4==0
                    RR_3=RR_3+1;
                    LR_4=LR_4-1;
                    R_3=XOR(R_4,R_3);
                end
            elseif RT_4==1
                RT_4=TRANSR(SNR,R_4);
                if RT_4==0
                    R_5=XOR(R_5,R_4);
                    LR_5=LR_5+1;
                    RR_4=RR_4-1;
                else
                    RT_4=1;
                end
            else
                if (RT_4==3)||(LR_4==1&&RR_4==1)
                    RT_4=TRANS2(SNR,R_4);
                    if RT_4==0
                        RR_3=RR_3+1;
                        R_3=XOR(R_4,R_3);
                        R_5=XOR(R_4,R_5);
                        LR_5=LR_5+1;
                        LR_4=LR_4-1;
                        RR_4=RR_4-1;
                    elseif RT_4==1
                        RR_3=RR_3+1;
                        LR_4=LR_4-1;
                        R_3=XOR(R_4,R_3);
                    elseif RT_4==2
                        LR_5=LR_5+1;
                        RR_4=RR_4-1;
                        R_5=XOR(R_4,R_5);
                    end
                end
            end
            
        case 2
              if RR_3==1||LRT_3==1 %节点3 左传
                LRT_3=TRANSR(SNR,R_3);
                if LRT_3==0
                    R_2=xor(R_3,R_2);
                    RR_2=RR_2+1;
                    RR_3=RR_3-1;
                end
              end
            
              if LR_5==1||RRT_5==1 %节点5 右传
                  RRT_5=TRANSR(SNR,R_5);
                  if RRT_5==0
                      LR_5=LR_5-1;
                      LR_6=LR_6+1;
                      output=output+1;
                      tend=[tend,time+4];
                  end
              end
              
        case 3
            if RT_2==2 % 节点2 双向
                RT_2=TRANSL(SNR,R_2);
                if RT_2==0
                    output=output+1;
                    RR_1=RR_1+1;
                    LR_2=LR_2-1;
                else
                    RT_2=2;
                end
            elseif RT_2==1
                RT_2=TRANSR(SNR,R_2);
                if RT_2==0
                    R_3=XOR(R_2,R_3);
                    LR_3=LR_3+1;
                    RR_2=RR_2-1;
                else
                    RT_2=1;
                end
            else
                if (RT_2==3)||(LR_2==1&&RR_2==1)
                    RT_2=TRANS2(SNR,R_2);
                    if RT_2==0
                        output=output+1;
                        RR_1=RR_1+1;
                        R_3=xor(R_2,R_3);
                        LR_3=LR_3+1;
                        LR_2=LR_2-1;
                        RR_2=RR_2-1;
                    elseif RT_2==1
                        output=output+1;
                        RR_1=RR_1+1;
                        LR_2=LR_2-1;
                    elseif RT_2==2
                        RR_2=RR_2-1;
                        R_3=XOR(R_2,R_3);
                        LR_3=LR_3+1;
                    end
                end
            end
            
            if LR_6==1||RT_6==1 %节点6 左传
                R_6=randi([0,1],1,data_bits);
                RT_6=TRANSR(SNR,R_6);
                if RT_6==0
                    R_5=XOR(R_5,R_6);
                    LR_6=LR_6-1;
                    RR_5=RR_5+1;
                end
            end
            
        case 4
           if LR_3==1||RRT_3==1 % 节点3 右传
                RRT_3=TRANSR(SNR,R_3);
                if RRT_3==0
                    R_4=XOR(R_4,R_3);
                    LR_4=LR_4+1;
                    LR_3=LR_3-1;
                end
           end
           
        case 0
            if RR_5==1||LRT_5==1 %节点5 左传
                LRT_5=TRANSR(SNR,R_5);
                if LRT_5==0
                    RR_4=RR_4+1;
                    RR_5=RR_5-1;
                    R_4=XOR(R_4,R_5);
                end
           end  
    end
    throughput(time) = output/(time+4);
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

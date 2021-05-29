function [ throughput] = SNCDM6_CORRECT (SNR)
data_bits=100;
slot=1000;
output=0;
empty=zeros(1,data_bits);
%中继节点初始化
X1=randi([0,1],1,data_bits);
Y1=randi([0,1],1,data_bits);
X2=randi([0,1],1,data_bits);
Y2=randi([0,1],1,data_bits);
RR1=empty;RL1=empty;SR1=Y1;SL1=X2;
RR2=Y1;RL2=empty;SR2=Y2;SL2=empty;
RR3=Y2;RL3=X1;SR3=empty;SL3=empty;
RR4=Y2;RL4=empty;SR4=X1;SL4=empty;

for time=1:slot %仿真时间
    type=mod(time,4); %将过程分为4个阶段
    switch type
        case 0
            if ~isequal(SR3,empty)&&~isequal(SL3,empty)          
                R_3=XOR(SR3,SL3);
                RR3=SR3;
                RL3=SL3;
                sign3=twoway(R_3,SNR);
                if sign3==1
                    SR2=XOR(R_3,RL2);
                    SL4=XOR(R_3,RR4);    
                elseif sign3==2
                    SR2=XOR(R_3,RL2);
                    SL4=empty;
                elseif sign3==3
                    SR2=empty;
                    SL4=XOR(R_3,RR4);
                end
            elseif ~isequal(SR3,empty)&&isequal(SL3,empty)
                R_3=SR3;
                RR3=SR3;
                if oneway(R_3,SNR)==1
                    SR2=XOR(R_3,RL2);
                else 
                    SR2=empty;
                end
            elseif isequal(SR3,empty)&&~isequal(SL3,empty)
                R_3=SL3;
                RL3=SL3;
                if oneway(R_3,SNR)==1
                    SL4=XOR(R_3,RR4);
                else
                    SL4=empty;
                end
            end               
  
        case 1
            if ~isequal(SR1,empty)&&~isequal(SL1,empty)          
                R_1=XOR(SR1,SL1);
                RR1=SR1;
                RL1=SL1;
                sign1=twoway(R_1,SNR);
                if sign1==1
                    output=output+1;
                    SL2=XOR(R_1,RR2);    
                elseif sign1==2
                    output=output+1;
                    SL2=empty;
                elseif sign1==3
                    SL2=XOR(R_1,RR2);
                end             
            elseif ~isequal(SR1,empty)&&isequal(SL1,empty)
                R_1=SR1;
                RR1=SR1;
                if oneway(R_1,SNR)==1
                    output=output+1;
                end
            elseif isequal(SR1,empty)&&~isequal(SL1,empty)
                R_1=SL1;
                RL1=SL1;
                if oneway(R_1,SNR)==1
                    SL2=SL1;
                else
                    SL2=empty;
                end
            end
            
            T2H=randi([0,1],1,data_bits);
            if oneway(T2H,SNR)==1
                SL4=T2H;
            else
                SL4=empty;
            end
            
        case 2
            H2T=randi([0,1],1,data_bits);
            if oneway(H2T,SNR)==1
                SR1=H2T;
            else
                SR1=empty;
            end
            
            if ~isequal(SR4,empty)&&~isequal(SL4,empty)          
                R_4=XOR(SR4,SL4);
                RR4=SR4;
                RL4=SL4;
                sign4=twoway(R_4,SNR);
                if sign4==1
                    output=output+1;
                    SR3=XOR(R_4,RL3);    
                elseif sign4==2
                    SR3=XOR(R_4,RL3);    
                elseif sign4==3
                    output=output+1;
                    SR3=empty;
                end             
            elseif ~isequal(SR4,empty)&&isequal(SL4,empty)
                R_4=SR4;
                RR4=SR4;
                if oneway(R_4,SNR)==1
                    SR3=SR4;
                else
                    SR3=empty;
                end
            elseif isequal(SR4,empty)&&~isequal(SL4,empty)
                R_4=SL4;
                RL4=SL4;
                if oneway(R_4,SNR)==1
                    output=output+1;
                end
            end
                    
        case 3
            if ~isequal(SR2,empty)&&~isequal(SL2,empty)          
                R_2=XOR(SR2,SL2);
                RR2=SR2;
                RL2=SL2;
                sign2=twoway(R_2,SNR);
                if sign2==1
                    SR1=XOR(R_2,RL1);
                    SL3=XOR(R_2,RR3);    
                elseif sign2==2
                    SR1=XOR(R_2,RL1);
                    SL3=empty;
                elseif sign2==3
                    SR1=empty;
                    SL3=XOR(R_2,RR3);
                end
            elseif ~isequal(SR2,empty)&&isequal(SL2,empty)
                R_2=SR2;
                RR2=SR2;
                if oneway(R_2,SNR)==1
                    SR1=XOR(R_2,RL1);
                else 
                    SR1=empty;
                end
            elseif isequal(SR2,empty)&&~isequal(SL2,empty)
                R_2=SL2;
                RL2=SL2;
                if oneway(R_2,SNR)==1
                    SL3=XOR(R_2,RR3);
                else
                    SL3=empty;
                end
            end               
    end
end
throughput=(output+1)/(slot+8);
end
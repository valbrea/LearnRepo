function [valid_throughput, FER, delay] = A2_N3_old (SNR, slot)
%数据包大小
data_bits=8742;
%每个节点的初始数据为空
AR=zeros(1,data_bits);
BR=zeros(1,data_bits);
CR=zeros(1,data_bits);
HR=zeros(1,data_bits);
TR=zeros(1,data_bits);
H2T=zeros(1,data_bits);
T2H=zeros(1,data_bits);
%其余数据

empty=zeros(1,data_bits);
prate=11*10^6; %物理链路层速率
T=data_bits/prate; %发送一次数据包所需时间
%接收缓存 
Atemp=empty;
Btemp=empty;
Ctemp=empty;
%重传状态
Htrans=0;
Atrans=0;
Btrans=0;
Ctrans=0;
Ttrans=0;
%接收标志
RH=1;
RA=1;LA=0;
RB=0;LB=0;
RC=1;LC=1;
LT=0;
hsend=0;
tsend=0;
hrecive=0;
trecive=0;
output=0;
valid = 0;
error = 0;
FER = 0;
for time=1:slot
    type=mod(time,3);
    switch type
        case 0 %B节点
            %B节点
            if Btrans==1
                Btrans=TRANSR(SNR,BR);
                if Btrans==0
                    LB=LB-1;
                    if Atrans==0
                        AR=xor(xor(AR,BR),Atemp); 
                        Atemp=empty;
                    else
                        Atemp=BR;
                    end
                    RA=RA+1;
                end
                
            elseif Btrans==2
                Btrans=TRANSL(SNR,BR);
                if Btrans==0
                    RB=RB-1;
                    if Ctrans==0
                        CR=xor(xor(CR,BR),Ctemp);
                        Ctemp=empty;
                    else
                        Ctemp=BR;
                    end
                    LC=LC+1;
                end
                
            elseif Btrans==3 % 两侧重传
                Btrans=TRANS2(SNR,BR);
                if Btrans==0
                    RB=RB-1;LB=LB-1;
                    if Ctrans==0
                        CR=xor(xor(CR,BR),Ctemp);
                        Ctemp=empty;
                        if Atrans==0
                            AR=xor(xor(AR,BR),Atemp);
                            Atemp=empty;  
                        else
                            Atemp=BR;
                        end
                    else
                        Ctemp=BR;
                        if Atrans==0
                            AR=xor(xor(AR,BR),Atemp);
                            Atemp=empty;  
                        else
                            Atemp=BR;
                        end                          
                    end
                    RA=RA+1;LC=LC+1;
                elseif Btrans==1
                    RB=RB-1;
                    if Ctrans==0
                        CR=xor(xor(CR,BR),Ctemp);
                        Ctemp=empty;
                    else
                         Ctemp=CR;
                    end
                    LC=LC+1;
                elseif Btrans==2
                    LB=LB-1;
                    if Atrans==0 
                        AR=xor(xor(AR,BR),Atemp);
                        Atemp=empty;   
                    else
                       Atemp=BR;
                    end
                    RA=RA+1;
                end
                
            elseif RB==1&&LB==1 % 为啥和Btrans == 3 一样
                Btrans=TRANS2(SNR,BR);
                if Btrans==0
                    RB=RB-1;LB=LB-1;
                    if Ctrans==0
                        CR=xor(xor(CR,BR),Ctemp);
                        Ctemp=empty;
                        if Atrans==0
                            AR=xor(xor(AR,BR),Atemp);
                            Atemp=empty;  
                        else
                            Atemp=BR;
                        end
                    else
                        Ctemp=BR;
                        if Atrans==0
                            AR=xor(xor(AR,BR),Atemp);
                            Atemp=empty;  
                        else
                            Atemp=BR;
                        end                          
                    end
                    RA=RA+1;LC=LC+1;
                elseif Btrans==1
                    RB=RB-1;
                    if Ctrans==0
                        CR=xor(xor(CR,BR),Ctemp);
                        Ctemp=empty;
                    else
                         Ctemp=CR;
                    end
                    LC=LC+1;
                elseif Btrans==2
                    LB=LB-1;
                    if Atrans==0 
                        AR=xor(xor(AR,BR),Atemp);
                        Atemp=empty;   
                    else
                       Atemp=BR;
                    end
                    RA=RA+1;
                end
            end
            
        case 1  %H C节点
            %H节点
            if Htrans==1
                Htrans=TRANSR(SNR,HR);
                if Htrans==0
                    hsend=[hsend,time];
                    RH=RH-1;
                    H2T=randi([0,1],1,data_bits);
                    HR=xor(HR,H2T);
                    if Atrans==0
                        AR=xor(xor(AR,HR),Atemp);
                        Atemp=empty;
                    else
                        Atemp=HR;
                    end
                    LA=LA+1; 
                end
                
            elseif RH==1
                Htrans=TRANSR(SNR,HR);
                if Htrans==0
                    hsend=[hsend,time];
                    RH=RH-1;
                    H2T=randi([0,1],1,data_bits);
                    HR=xor(HR,H2T);
                    if Atrans==0
                        AR=xor(xor(AR,HR),Atemp);
                        Atemp=empty;
                    else
                        Atemp=HR;
                    end
                    LA=LA+1;
                end
            end
            
            %C节点
            if Ctrans==1
                Ctrans=TRANSR(SNR,CR);
                if Ctrans==0 
                    LC=LC-1;
                    if Btrans==0
                        BR=xor(xor(CR,BR),Btemp);
                        Btemp=empty;
                    else
                        Btemp=CR;
                    end
                    RB=RB+1;
                end
                
            elseif Ctrans==2
                Ctrans=TRANSL(SNR,CR);
                if Ctrans==0
                    RC=RC-1;
                    TR=xor(CR,T2H);
                    if ~isequal(TR,empty)&&~isequal(CR,empty)
                        valid=valid+1;
                        trecive=[trecive,time];
                    else
                        error = error + 1;
                    end
                    LT=LT+1;
                end
                
            elseif Ctrans==3
                Ctrans=TRANS2(SNR,CR);
                if Ctrans==0
                    RC=RC-1;LC=LC-1;
                    TR=xor(CR,T2H);
                    if ~isequal(TR,empty)&&~isequal(CR,empty)
                        valid=valid+1;
                        trecive=[trecive,time];
                        else
                        error = error + 1;
                    end
                    if Btrans==0
                        BR=xor(xor(CR,BR),Btemp);
                        Btemp=empty;
                    else
                        Btemp=CR;
                    end
                    RB=RB+1;LT=LT+1;
                elseif Ctrans==1
                    RC=RC-1;
                    TR=xor(CR,T2H);
                    if ~isequal(TR,empty)&&~isequal(CR,empty)
                        valid=valid+1;
                        trecive=[trecive,time];
                        else
                        error = error + 1;
                    end
                    LT=LT+1;
                elseif Ctrans==2
                    LC=LC-1;
                    if Btrans==0
                        BR=xor(xor(CR,BR),Btemp);
                        Btemp=empty;
                    else
                        Btemp=CR;
                    end
                    RB=RB+1;
                end
                
            elseif RC==1&&LC==1
                Ctrans=TRANS2(SNR,CR);
                if Ctrans==0
                    RC=RC-1;LC=LC-1;
                    TR=xor(CR,T2H);
                    if ~isequal(TR,empty)&&~isequal(CR,empty)
                        valid=valid+1;
                        trecive=[trecive,time];
                        else
                        error = error + 1;
                    end
                    if Btrans==0
                        BR=xor(xor(CR,BR),Btemp);
                        Btemp=empty;
                    else
                        Btemp=CR;
                    end
                    RB=RB+1;LT=LT+1;
                elseif Ctrans==1
                    RC=RC-1;
                    TR=xor(CR,T2H);
                    if ~isequal(TR,empty)&&~isequal(CR,empty)
                        valid=valid+1;
                        trecive=[trecive,time];
                        else
                        error = error + 1;
                    end
                    LT=LT+1;
                elseif Ctrans==2
                    LC=LC-1;
                    if Btrans==0
                        BR=xor(xor(CR,BR),Btemp);
                        Btemp=empty;
                    else
                        Btemp=CR;
                    end
                    RB=RB+1;
                end
            end
            
        case 2 %A T节点
            %A节点
            if Atrans==1
                Atrans=TRANSR(SNR,AR);
                if Atrans==0
                    LA=LA-1;
                    HR=xor(AR,H2T);
                    if ~isequal(HR,empty)&&~isequal(AR,empty)
                        valid=valid+1;
                        hrecive=[hrecive,time];
                        else
                        error = error + 1;
                    end
                    RH=RH+1;
                end
                
            elseif Atrans==2
                Atrans=TRANSL(SNR,AR);
                if Atrans==0
                    RA=RA-1;
                    if Btrans==0
                        BR=xor(xor(BR,AR),Btemp);
                        Btemp=empty;
                    else
                        Btemp=AR;
                    end
                    LB=LB+1;
                end
                
            elseif Atrans==3
                Atrans=TRANS2(SNR,AR);
                if Atrans==0
                    RA=RA-1;LA=LA-1;
                    HR=xor(AR,H2T);
                    if ~isequal(HR,empty)&&~isequal(AR,empty)
                        valid=valid+1;
                        hrecive=[hrecive,time];
                        else
                        error = error + 1;
                    end
                    if Btrans==0
                        BR=xor(xor(AR,BR),Btemp);
                        Btemp=empty;
                    else
                        Btemp=AR;
                    end
                    LB=LB+1;RH=RH+1;
                elseif Atrans==1
                    RA=RA-1;
                    if Btrans==0
                        BR=xor(xor(BR,AR),Btemp);
                        Btemp=empty;
                    else
                        Btemp=AR;
                    end
                    LB=LB+1;
                elseif Atrans==2
                    LA=LA-1;
                    HR=xor(AR,H2T);
                    if ~isequal(HR,empty)&&~isequal(AR,empty)
                        valid=valid+1;
                        hrecive=[hrecive,time];
                        else
                        error = error + 1;
                    end
                    RH=RH+1;
                end
                
            elseif RA==1&&LA==1
                Atrans=TRANS2(SNR,AR);
                if Atrans==0
                    RA=RA-1;LA=LA-1;
                    HR=xor(AR,H2T);
                    if ~isequal(HR,empty)&&~isequal(AR,empty)
                        valid=valid+1;
                        hrecive=[hrecive,time];
                        else
                        error = error + 1;
                    end
                    if Btrans==0
                        BR=xor(xor(AR,BR),Btemp);
                        Btemp=empty;
                    else
                        Btemp=AR;
                    end
                    LB=LB+1;RH=RH+1;
                elseif Atrans==1
                    RA=RA-1;
                    if Btrans==0
                        BR=xor(xor(BR,AR),Btemp);
                        Btemp=empty;
                    else
                        Btemp=AR;
                    end
                    LB=LB+1;
                elseif Atrans==2
                    LA=LA-1;
                    HR=xor(AR,H2T);
                    if ~isequal(HR,empty)&&~isequal(AR,empty)
                        valid=valid+1;
                        hrecive=[hrecive,time];
                        else
                        error = error + 1;
                    end
                    RH=RH+1;
                end
            end
            
            %T节点
            if Ttrans==1
                Ttrans=TRANSR(SNR,TR);
                if Ttrans==0
                    tsend=[tsend,time];
                    LT=LT-1;
                    T2H=randi([0,1],1,data_bits);
                    TR=xor(TR,T2H);
                    if Ctrans==0
                        CR=xor(xor(CR,TR),Ctemp);
                        Ctemp=empty;      
                    else
                        Ctemp=TR;
                    end
                    RC=RC+1;
                end
                
            elseif LT==1
                Ttrans=TRANSR(SNR,TR);
                if Ttrans==0
                    tsend=[tsend,time];
                    LT=LT-1;
                    T2H=randi([0,1],1,data_bits);
                    TR=xor(TR,T2H);
                    if Ctrans==0
                        CR=xor(xor(CR,TR),Ctemp);
                        Ctemp=empty;
                    else
                        Ctemp=TR;
                    end
                    RC=RC+1;
                end
            end  
    end
    throughput(time) = output / time; % 吞吐量
    valid_throughput(time) = valid/time;
end
output = valid + error;
FER = error ./ output;
% 计算时延
h=length(hrecive);
t=length(trecive);
hsend=hsend(:,2:t);
hrecive=hrecive(:,2:h);
tsend=tsend(:,2:h);
trecive=trecive(:,2:t);
delay=[trecive-hsend,hrecive-tsend];
delay=mean(delay(:))+1;


%figure, hold on;
%plot(throughput, 'r');
% plot(valid_throughput, 'b');
%xlabel('timeslot'), ylabel('throughput');
end
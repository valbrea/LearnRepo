function E = CTPI(P,varargin)
% CTPI --- Cross-Talk Error, Performance index of a separation algorithm.
%          P=WA(or WVA), where W is demixed matrix, A is mixing
%          matrix and V is whitening matrix. The larger the value
%          E is, the poorer the statistical performance of a 
%          separation algorithm.
%
% The computer formula is as following:
%                N      N     |P(i,j)|               N      N     |P(j,i)|         
%   SIRPI(P) =  sum (  sum --------------- - 1  ) + sum (  sum --------------- - 1  )
%               i=1    j=1  max(|P(i,j)|)           j=1    i=1  max(|P(j,i)|)
% Format:
%          E = CTPI(P,'sum');     compute the SIRPI above
%          E = CTPI(P,'ave');     compute the average SIRPI, that is, SIRPI/N             
%          E = CTPI(P);           default value, compute the SIRPI
%
% Parameter:
% < Input >
%            P --- P=WA(or WVA),where W is demixed matrix and A is mixing matrix
%                  and whose P(i,j) is the ijth element of the N*N matrix P
%        'sum' --- compute the SIRPI above
%        'ave' --- compute the average SIRPI, that is, SIRPI/N^2 
%
% References:
%  [1] S. Amari, A. Cichocki and H. Yang 1996, A new
%      learning algorithm for blind signal separation. in
%      Advances in Neural Information Processing Systems
%      8 (MIT Press, Cambridge, MA), pp. 757-763.
%
% Author  : Zhi-Lin Zhang ( zhangzl@vip.163.com )
% Version : 1.1
% Date    : Dec.27, 2004 
% Update  : Mar.3, 2005


[I,J] = size(P);
P = abs(P);
if I == J
    N = I;  % the order of the matrix P
else
    fprintf('Number of columns are NOT equal to that of lines!\nExit...\n');
    return;
end

sum1 = 0;
for i = 1:N
    maxEle = max(P(i,:));
    sum1 = sum1 + sum(P(i,:))/maxEle;
end
sum1 = sum1 - N;

sum2 = 0;
for j = 1:N
    maxEle = max(P(:,j));
    sum2 = sum2 + sum(P(:,j))/maxEle;
end
sum2 = sum2 - N;

E = sum1 + sum2;
    
vin = length(varargin);
if vin == 1
    switch lower(varargin{1})
        case 'sum'  
            % if want to obtain non-averaged performance index, then accepte
            % the E, which has already computed.
            
        case 'ave'  
            % if want to compute the average performance index, then 
            E = E/N;
            
        otherwise
            % wrong input parameter
            error(['Unrecognized parameter: ''' varargin{1} '''']);
    end
end

% if vin ==0, implying the user wants the non-averaged performance index,
% then directly accepte the E
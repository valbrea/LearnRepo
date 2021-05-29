classdef EndNode
    % 节点类
    properties
        % 关键词properties：用来存放类的属性（成员变量），以end结束
        number;
        type;
        PB;
        TB;
    end
    
    methods
        % 关键词methods：用来存放类的方法（成员函数），以end结束
        function obj = EndNode(num, packet_lenght)
            obj.number = num;
            obj.type = mod(obj.number, 3);
            obj.PB = zeros(1, packet_lenght);
            obj.TB = zeros(1, packet_lenght);
        end
    end
    
end % 类结束

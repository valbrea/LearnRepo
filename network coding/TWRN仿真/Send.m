function[] = Send(node_i, n)
switch node_i.number
    case 0
        % 头节点发送
    case n + 1
        % 尾节点发送
    otherwise
        % 中继节点发送
end

end
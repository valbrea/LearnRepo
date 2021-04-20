 class Solution2 {
    public static void main(String[] args) {
        int less = 0;
        ListNode min = new ListNode(0);//存放最小值
        int len = count(head);
        int min = head.val;
        copy(min,head);
        ListNode temp = head;
        for (int i = 0;i<len;i++){
            如果下一个值比min头节点小或相等，就把前面的节点都扔到后面；
                如果是小，把这个新链表复制给min；
                如果相等，就先比较链表，然后再决定是否复制；
              if (String[i] <= min)
        }
        return min.next;
    }

    public int count(ListNode head){ //head1<head2就返回true
        temp1 = head1;
        int len = 0;
        while (temp1!=null){
            len++;
            temp1 = temp1.next;
        }
        return len;
    }

    public boolean cmp(ListNode head1,ListNode head2){ //head1<head2就返回true
        temp1 = head1;
        temp2 = head2;
        while (temp1!=null){
            if(temp1.val>temp2.val){
                return  false;
            }
            temp1 = temp1.next;
            temp2 = temp2.next;
        }
        return true;
    }

    public copy(ListNode head1,ListNode head2){ //把小的复制到result
        temp1 = head1;
        temp2 = head2;
        while(temp1!=null){
            ListNode next = new ListNode(temp1.val);
            temp2.next = next;
            temp1 = temp1.next;
            temp2 = temp2.next;
        }
    }
}
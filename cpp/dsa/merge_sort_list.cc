// 有序列表的二路归并：
// 当前列表中自p_first起的first_size个元素，与列表lst中自p_second起的second_size个元素归并
// 这里由于需要在函数里改变p_first所指的位置，需要指向p_first的引用
void Merge(ListNode *&p_first, int first_size, List<T> &lst, ListNode *p_second,
           int second_size) {
  ListNode *pp = p_first->pre_;
  while (second_size > 0) { // 若第二个链表没合并完
    // 若第一个链表没合并完且第一个链表中节点的数据 <= 第二个链表中节点的数据
    if ((first_size > 0) && (p_first->data_ >= p_second->data_)) { //重载>=
      // 第一个链表归入合并的链表，并替换为其直接后继
      p_first = p_first->suc_;
      if (p_second == p_first)
        break; // 如果第一个链表耗尽则结束
      --first_size;
    } else {
      // 若第一个链表已经耗尽，或第一个链表中节点的数据>第二个链表中节点的数据
      // 在第一个链表的前面插入第二个链表中的p_second元素
      ListNode *temp = p_second;
      p_second = p_second->suc_;
      InsertBefore(p_first, lst.DeleteNode(temp));
      --second_size;
    }
  }
  p_first = pp->suc_; // 确定归并后区间的起点
}
// 这里由于需要在函数里改变p_first所指的位置，需要指向p_first的引用
void MergeSort(ListNode *&p_begin, int size) {
  if (size < 2)
    return;
  int mid = size >> 1;
  ListNode *p_mid = p_begin;
  for (int i(0); i < mid; ++i)
    p_mid = p_mid->suc_;        // elem_mid指向mid处
  MergeSort(p_begin, mid);      // 归并排序[1, mid)
  MergeSort(p_mid, size - mid); // 归并排序[mid, tail)
  Merge(p_begin, mid, *this, p_mid, size - mid);
  // Print(p_begin, size);
}
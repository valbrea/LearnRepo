/*
3. DNA排序
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
现在有一些长度相等的DNA串（只由ACGT四个字母组成），请将它们按照逆序对的数量多少排序。

逆序对指的是字符串A中的两个字符A[i]、A[j]，具有i < j 且 A[i] > A[j] 的性质。如字符串”ATCG“中，T和C是一个逆序对，T和G是另一个逆序对，这个字符串的逆序对数为2。

输入
第1行：两个整数n和m，n(0<n<=50)表示字符串长度，m(0<m<=100)表示字符串数量

第2至m+1行：每行是一个长度为n的字符串

输出
按逆序对数从少到多输出字符串，逆序对数一样多的字符串按照输入的顺序输出。

样例输入
10 6
AACATGAAGG
TTTTGGCCAA
TTTGGCCAAA
GATCAGATTT
CCCGGGGGGA
ATCGATGCAT
样例输出
CCCGGGGGGA
AACATGAAGG
GATCAGATTT
ATCGATGCAT
TTTTGGCCAA
TTTGGCCAAA
*/
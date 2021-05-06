#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;

//判断运算符号优先级是否满足c1>=c2
bool prior(const char c1, const char c2) {
  if ((c1 == '-' || c1 == '+') && (c2 == '*' || c2 == '/'))
    return false;
  else
    return true;
}

//函数Op2Num(): 操作两个数字的运算;
void Op2Num(stack<int> &num, stack<char> &op) {
  int num1, num2; //取数字栈顶的两个操作数
  num1 = num.top();
  num.pop();
  num2 = num.top();
  num.pop();
  switch (op.top()) { //操作数字栈顶两数字并重新入栈
  case '+':
    num.push(num2 + num1);
    break;
  case '-':
    num.push(num2 - num1);
    break;
  case '*':
    num.push(num2 * num1);
    break;
  case '/':
    num.push(num2 / num1);
    break;
  default:
    printf("       something wrong in Op2Num\n");
  }
  op.pop(); //弹出符号栈顶符号
}

//函数OpeNum():
// cur传入字符')','+','-','*','/',表明调用本函数的触发条件
void OpeNum(stack<int> &num, stack<char> &op, char cur) {
  while (!op.empty() && op.top() != '(' && prior(op.top(), cur))
    Op2Num(num, op);
  switch (cur) {
  case ')':
    if (op.top() == '(')
      op.pop(); //弹左括号
    break;
  default:
    op.push(cur); //当前符号入符号栈
  }
  return;
}

//从字符串中取数字
int GetNum(char *str, int &i) {
  int temp = 0;
  while (str[i] >= '0' && str[i] <= '9') {
    temp = temp * 10 + str[i] - '0';
    ++i;
  }
  --i;
  return temp;
}

//表达式结束，所有符号弹栈
void PopAll(stack<int> &num, stack<char> &op) {
  while (!op.empty())
    Op2Num(num, op);
  return;
}

//中缀表达式运算
int CalNifix(char *str) {
  stack<int> num; //数字栈
  stack<char> op; //符号栈
  for (int i = 0; str[i]; ++i) {
    switch (str[i]) {
    case '(':
      op.push('(');
      break; //左括号入栈
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
      OpeNum(num, op, str[i]);
      break; //操作运算
    default:
      num.push(GetNum(str, i)); //取数字入数字栈
    }
  }
  PopAll(num, op);  //表达式结束，所有符号弹栈
  return num.top(); //返回运算结果
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    char str[650]; //储存中缀表达式
    scanf("%s", str);
    printf("%d\n", CalNifix(str));
  }
  return 0;
}
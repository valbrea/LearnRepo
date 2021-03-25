#include <iostream>
using namespace std;
void f(int *a, int *b) {
  int *c;
  c = a;
  a = b;
  b = c;
}
int main() {
  int x = 3, y = 5, *p = &x, *q = &y;
  f(p, q);
  cout << *p << ' ' << *q << endl;
  f(&x, &y);
  cout << *p << ' ' << *q << endl;

  return 0;
}
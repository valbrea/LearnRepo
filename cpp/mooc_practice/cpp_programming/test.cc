#include <iostream>
using namespace std;
char *op( char *a) {
  char *b = a;
  return b;
}
int main() {
  char *a1 = "a1";
  char *a2 = "a2";
  cout << op(a1) << endl;
  cout << op(a2) << endl;
  return 0;
}
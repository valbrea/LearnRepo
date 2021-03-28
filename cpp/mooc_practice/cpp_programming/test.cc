#include <climits>
#include <cmath>
#include <iostream>
using namespace std;
int main() {
  // cout << sizeof(long long) << endl;
  // cout << sizeof(long) << endl;
  // cout << sizeof(int) << endl;
  // cout << sizeof(short) << endl;
  // cout << sizeof(long double) << endl;
  // cout << sizeof(double) << endl;
  // cout << sizeof(double) << endl;
  long long a = LLONG_MAX;
  unsigned long long b = ULLONG_MAX;
  unsigned long long c = b - a - a;
  long long d = c % LLONG_MAX;
  cout << a << endl << b << endl << c << endl << d << endl;
  cout << to_string(a).length() << endl;
  return 0;
}
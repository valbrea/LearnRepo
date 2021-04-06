#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;
  cin.ignore();
  vector<int> num;
  string str;
  cin >> str;
  int m[n];
  for (int j(0); j <n; ++j) {
    m[j] = stoi(str.substr(j, 1));
    num.push_back(m[j]);
  }
  int last_lenght = n, count(0);
  vector<int>::iterator i;
  for (int j(0); j < (n / 2); ++j) {
    for (i = num.begin(); i != num.end(); ++i) {
      if (*i + *(i + 1) == 10) {
        num.erase(i, i + 2);
        count += 2;
        break;
      }
    }
  }
  last_lenght -= count;
  cout << last_lenght << endl;

  return 0;
}

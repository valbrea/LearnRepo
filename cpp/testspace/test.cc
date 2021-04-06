#include <iostream>
#include <string>
#include <vector>
using namespace std;
int n;
inline int Xiaoqu(vector<int> &p) {
  int last_lenght = p.size(), count(0);1`xw 
  for (int j(0); j < (last_lenght / 2); ++j) {
    for (i = p.begin(); i != p.end(); ++i) {
      if (*i + *(i + 1) == 10) {
        p.erase(i, i + 2);
        count += 2;
        break;
      }
    }
  }
  last_lenght -= count;
  return last_lenght;
}

int main() {
  cin >> n;
  cin.ignore();
  vector<int> num;
  string str;
  cin >> str;
  int m[str.length()];
  for (int j(0); j < str.length(); ++j) {
    m[j] = stoi(str.substr(j, 1));
    num.push_back(m[j]);
  }

  cout << Xiaoqu(num) << endl;

  return 0;
}

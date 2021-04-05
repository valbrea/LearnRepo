#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
  int t(0);
  cin >> t;
  while (t > 0) {
    int n(0);
    cin >> n;
    int time[n], min_time(100000);
    for (int i(0); i < n; ++i) {
      cin >> time[i];
      if (time[i] < min_time)
      min_time = time[i];
    }
    

    cout << min_time << endl;
    --t;
  }

  return 0;
}
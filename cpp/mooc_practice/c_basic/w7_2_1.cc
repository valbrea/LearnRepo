/*****************************************************************************************
 * #1 年龄与疾病
 * 某医院想统计一下某项疾病的获得与否与年龄是否有关，需要对以前的诊断记录进行整理。
 * 输入
 * 共2行，第一行为过往病人的数目n（0 < n <= 100)，第二行为每个病人患病时的年龄。
 * 输出
 * 每个年龄段（分四段：18以下，19-35，36-60，大于60注意看样例输出的格式）的患病人数占总患病人数的比例，
 * 以百分比的形式输出，精确到小数点后两位（double）。
 * 关于c++的格式化的输入输出，请参考：http://www.cplusplus.com/reference/iomanip。
 * 也可以在网上搜索一下，资料很多的。
 * **************************************************************************************/

#include <iomanip>
#include <iostream>
using namespace std;

int main() {
  int total;
  // cout << "输入病人数目。" << endl;
  cin >> total;
  int age[total];
  // cout << "输入每个病人患病时的年龄。" << endl;
  for (int i(0); i < total; i++) {
    cin >> age[i];
  }

  int sum[4] = {};
  double percent[4] = {};

  for (int j(0); j < total; j++) {
    if (age[j] <= 18) {
      sum[0]++;
    } else if (19 <= age[j] && age[j] <= 35) {
      sum[1]++;
    } else if (36 <= age[j] && age[j] <= 60) {
      sum[2]++;
    } else if (60 <= age[j]) {
      sum[3]++;
    } else {
      cout << "ERROR!" << endl;
    }
  }

  for (int k(0); k < 4; k++) {
    percent[k] = (double)sum[k] / (double)total * 100;
  }

  cout << fixed << setprecision(2);
  cout << "1-18: " << percent[0] << "%" << endl;
  cout << "19-35: " << percent[1] << "%" << endl;
  cout << "36-60: " << percent[2] << "%" << endl;
  cout << "60-: " << percent[3] << "%" << endl;

  return 0;
}
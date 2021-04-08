#include <iomanip>
#include <iostream>
#include <cstring>
using namespace std;

class Camp {
private:
  string camp_name_;
  int worrior_number_, qty_[5], camp_strength_;
  string worrior_type_in_order_[5];
  int strength_in_order_[5], atk_in_order_[5], index_;

public:
  static int min_strength_, time_, camp_strength_per_, strength_per_[5];
  static const int red_seq_[5], blue_seq_[5];
  static const string worrior_type_[5];

  Camp(const string camp_name);
  int BuildWarriors();
};

Camp::Camp(const string camp_name)

    : camp_name_(camp_name), worrior_number_(0), qty_(),
      camp_strength_(camp_strength_per_), worrior_type_in_order_(),
      strength_in_order_(), atk_in_order_(), index_(0) {
  time_ = 0;
  const int *seq;
  if (camp_name == "red") {
    seq = red_seq_;
  } else if (camp_name == "blue") {
    seq = blue_seq_;
  } else {
    cout << "camp_name error!" << endl;
  }
  min_strength_ = camp_strength_;
  for (int i(0); i < 5; ++i) {
    worrior_type_in_order_[i] = worrior_type_[seq[i]];
    strength_in_order_[i] = strength_per_[seq[i]];
    if (strength_in_order_[i] < min_strength_)
      min_strength_ = strength_in_order_[i];
  }
}

int Camp::time_ = 0, Camp::min_strength_ = 0,
    Camp::camp_strength_per_(0), Camp::strength_per_[5] = {0};
const int Camp::red_seq_[5] = {2, 3, 4, 1, 0},
          Camp::blue_seq_[5] = {3, 0, 1, 2, 4};
const string Camp::worrior_type_[5] = {"dragon", "ninja", "iceman", "lion",
                                       "wolf"};

int main() {
  int n(0);
  cin >> n;
  do {

    cin >> Camp::camp_strength_per_;
    for (int i(0); i < 5; ++i) {
      cin >> Camp::strength_per_[i];
    }
    cout << "Case:" << n << endl;

    Camp red("red");
    Camp blue("blue");

    int r_end(0), b_end(0);
    while (r_end == 0 || b_end == 0) {
      if (r_end == 0)
        r_end = red.BuildWarriors();
      if (b_end == 0)
        b_end = blue.BuildWarriors();
      ++Camp::time_;
    }
  } while (--n > 0);

  return 0;
}

int Camp::BuildWarriors() {
  if (Camp::camp_strength_ < Camp::min_strength_) {
    cout << setw(3) << setfill('0') << Camp::time_ << ' ' << camp_name_
         << " headquarter stops making warriors" << endl;
    return 2;
  } else {

    while (Camp::camp_strength_ < strength_in_order_[index_]) {
      if (index_ != 4)
        index_++;
      else
        index_ = 0;
    }
    ++worrior_number_;
    Camp::camp_strength_ -= strength_in_order_[index_];
    ++qty_[index_];

    cout << setw(3) << setfill('0') << Camp::time_ << ' ' << camp_name_ << ' '
         << worrior_type_in_order_[index_] << ' ' << worrior_number_
         << " born with strength " << strength_in_order_[index_] << ','
         << qty_[index_] << ' ' << worrior_type_in_order_[index_] << " in "
         << camp_name_ << " headquarter" << endl;
    ++index_;
    return 0;
  }
}

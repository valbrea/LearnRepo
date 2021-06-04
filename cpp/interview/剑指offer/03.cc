#include <vector>
class Solution {
public:
  int findRepeatNumber(vector<int> &nums) {
    int hash[1000001];
    memset(hash, 0, sizeof(hash));
    for (int i = 0; i < nums.end(); ++i) {
      if (hash[nums[i]] == 0) {
        hash[nums[i]] = 1;
      } else {
        return nums[i];
      }
    }
  }
};
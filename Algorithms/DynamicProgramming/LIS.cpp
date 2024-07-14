#include <limits.h>

#include <algorithm>
#include <iostream>
#include <vector>

std::pair<int, std::vector<int>> LongestIncreasingSubsequence(
    std::vector<int>& nums) {
  int n = nums.size();
  std::vector<int> dp(n + 1, INT_MAX);
  std::vector<int> pos(n + 1, -1);
  std::vector<int> prev(n, -1);
  int length = 0;
  dp[0] = INT_MIN;

  for (int i = 0; i < n; ++i) {
    int j = std::lower_bound(dp.begin(), dp.end(), nums[i]) - dp.begin();
    if (dp[j - 1] < nums[i] && nums[i] < dp[j]) {
      dp[j] = nums[i];
      pos[j] = i;
      prev[i] = pos[j - 1];
      length = std::max(length, j);
    }
  }

  // Backtracking to find the LIS array
  std::vector<int> lis(length);
  int p = pos[length];
  int i = 0;
  while (p != -1) {
    lis[i++] = nums[p];
    p = prev[p];
  }

  std::reverse(lis.begin(), lis.end());
  return {length, lis};
}

int main() {
  std::vector<int> v = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};

  auto lis = LongestIncreasingSubsequence(v);
  std::cout << lis.first << '\n';
  for (auto& elem : lis.second) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}
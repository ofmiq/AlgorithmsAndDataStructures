#include <iostream>
#include <vector>

/*
Требуется найти количество разложений числа n на различные слогаемые
*/

int partitions(int n) {
  std::vector<int> dp(n + 1, 0);
  dp[0] = 1;

  for (int i = 1; i <= n; ++i) {
    for (int j = n; j >= i; --j) {
      dp[j] += dp[j - i];
    }
  }

  return dp[n];
}

int main() {
  int n = 7;
  std::cout << partitions(n) << '\n';
}
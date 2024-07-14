#include <iostream>
#include <vector>

/*
принимает на вход целое число n и возвращает количество
различных путей которыми можно добраться до ступеньки n
(подниматься можно или на 1 или на 2 ступеньки вверх)
*/

int stairs(int n) {
  if (n == 0 || n == 1) {
    return 1;
  }

  std::vector<int> dp(n + 1);
  dp[0] = dp[1] = 1;

  for (int i = 2; i <= n; i++) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }
  return dp[n];
}

int main() { std::cout << stairs(37) << '\n'; }

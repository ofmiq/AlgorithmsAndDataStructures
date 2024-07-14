#include <iostream>
#include <vector>

/*
принимает на вход целое число n и возвращает массив,
содержащий количество единиц в битовом представлении
каждого числа от 0 до n включительно
*/

std::vector<int> bits(int n) {
  std::vector<int> dp(n+1);
  for (int i = 1; i <= n; ++i) {
    dp[i] = dp[i >> 1] + (i & 1);
  }
  return dp;
}

int main() {
  std::vector<int> result = bits(5);
  for (const int& elem : result) {
    std::cout << elem << '\n';
  }
}
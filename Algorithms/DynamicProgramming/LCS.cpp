#include <iostream>
#include <vector>

std::pair<int, std::string> LongestCommonSubsequence(const std::string& s1,
                                                     const std::string& s2) {
  int m = s1.length();
  int n = s2.length();
  std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i][j - 1], dp[i - 1][j]);
      }
    }
  }

  // Backtracking to find the LCS string
  int index = dp[m][n];
  std::string lcs(index, ' ');

  int i = m, j = n;
  while (i > 0 && j > 0) {
    if (s1[i - 1] == s2[j - 1]) {
      lcs[index - 1] = s1[i - 1];
      --i;
      --j;
      --index;
    } else if (dp[i - 1][j] > dp[i][j - 1]) {
      --i;
    } else {
      --j;
    }
  }

  return {dp[m][n], lcs};
}

int main() {
  std::string s1 = "XMJYAUZ";
  std::string s2 = "MZJAWXU";
  auto result = LongestCommonSubsequence(s1, s2);
  std::cout << "Length of LCS: " << result.first << '\n';
  std::cout << "LCS: " << result.second << '\n';
}
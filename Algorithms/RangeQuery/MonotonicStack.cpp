#include <iostream>
#include <stack>
#include <vector>

std::vector<int> MonotonicIncreasingStack(const std::vector<int>& array) {
  int n = array.size();
  std::vector<int> result(n, -1);
  std::stack<int> stk;

  for (int i = 0; i < n; ++i) {
    while (!stk.empty() && array[stk.top()] >= array[i]) {
      stk.pop();
    }
    if (!stk.empty()) {
      result[i] = array[stk.top()];
    }
    stk.push(i);
  }

  return result;
}

std::vector<int> MonotonicDecreasingStack(const std::vector<int>& array) {
  int n = array.size();
  std::vector<int> result(n, -1);
  std::stack<int> stk;

  for (int i = 0; i < n; ++i) {
    while (!stk.empty() && array[stk.top()] <= array[i]) {
      stk.pop();
    }
    if (!stk.empty()) {
      result[i] = array[stk.top()];
    }
    stk.push(i);
  }

  return result;
}

void PrintArray(const std::vector<int>& array) {
  for (const auto& elem : array) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6};

  std::vector<int> min_left = MonotonicIncreasingStack(nums);
  std::cout << "Nearest smaller for the each element: ";
  PrintArray(min_left);

  std::vector<int> max_left = MonotonicDecreasingStack(nums);
  std::cout << "Nearest larger for the each element: ";
  PrintArray(max_left);
}

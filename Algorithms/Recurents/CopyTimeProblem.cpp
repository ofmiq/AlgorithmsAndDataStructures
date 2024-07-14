#include <iostream>
#include <algorithm>

int MinTimeToPrint(int x, int y, int n) {
  int min1 = std::min(x, y);
  
  if (n == 1) {
    return min1;
  }

  int left = 0;
  int right = n * (x + y - min1 + 1);
  
  while (right - left > 1) {
    int middle = (right + left) / 2;
    if (n - 1 <= middle / x + middle / y) {
      right = middle;
    } else {
      left = middle;
    }
  }
  
  return min1 + left + 1;
}

int main() {
  int time1 = 3;
  int time2 = 5;
  int n = 4;
  std::cout << MinTimeToPrint(time1, time2, n) << '\n';
}

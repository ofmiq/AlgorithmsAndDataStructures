#include <iostream>

int GCDRemainderWay(int a, int b) {
  while (a != 0 && b != 0) {
    if (a > b) {
      a -= b;
    } else {
      b -= a;
    }
  }
  return a + b;
} // O(max(a, b))

int GCDModuleWay(int a, int b) {
  while (a != 0 && b != 0) {
    if (a > b) {
      a %= b;
    } else {
      b %= a;
    }
  }
  return a + b;
} // O(log min(a, b))


int main() {
  std::cout << GCDRemainderWay(1, 100) << '\n';
  std::cout << GCDModuleWay(36, 24) << '\n';
}
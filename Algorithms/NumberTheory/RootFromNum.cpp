#include <iostream>

double squareRoot(double n, double precision = 1e-10) {
  double left = 0.0;
  double right = n / 2;
  
  while (right - left > precision) {
    double mid = left + (right - left) / 2;
    if (mid * mid <= n) {
      left = mid;
    }
    else {
      right = mid;
    }  
  }
  
  return left;
}

int main() {
    std::cout << squareRoot(50) << '\n';
    return 0;
}

#include <cstdint>
#include <iostream>

struct Point {
  int64_t x;
  int64_t y;
};

struct Line {
  int64_t a;
  int64_t b;
  int64_t c;
};

bool is_same_half_plane(const Point p1, const Point p2, const Line line) {
  double value1 = line.a * p1.x + line.b * p1.y + line.c;
  double value2 = line.a * p2.x + line.b * p2.y + line.c;
  return ((value1 > 0 && value2 > 0) || (value1 < 0 && value2 < 0));
}

int main() {
  Point p1{-1, 1};
  Point p2{2, 2};
  Line line{2, 3, -2};

  bool result = is_same_half_plane(p1, p2, line);
  std::cout << std::boolalpha << result << '\n';
}
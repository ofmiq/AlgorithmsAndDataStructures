#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

struct Point {
  int64_t x;
  int64_t y;
};

double oriented_area(const std::vector<Point>& polygon) {
  int n = polygon.size();
  double area = 0.0;

  for (int i = 0; i < n; ++i) {
    Point current = polygon[i];
    Point next = polygon[(i + 1) % n];

    long long vector_x = next.x - current.x;
    long long vector_y = next.y - current.y;

    area += vector_x * next.y - vector_y * next.x;
  }

  area = std::abs(area) / 2.0;

  return area;
}

int main() {
  /*
  int N;
  std::cin >> N;

  std::vector<Point> vertices(N);
  for (int i = 0; i < N; ++i) {
    std::cin >> vertices[i].x >> vertices[i].y;
  }
  */

  std::vector<Point> vertices {{1, 1}, {1, 4}, {7, 4}};
  double resultArea = oriented_area(vertices);
  std::cout << resultArea << '\n';
}
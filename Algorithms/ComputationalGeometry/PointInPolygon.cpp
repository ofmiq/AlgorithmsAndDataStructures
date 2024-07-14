#include <cstdint>
#include <iostream>
#include <vector>

struct Point {
  int64_t x;
  int64_t y;
};

bool is_point_in_polygon(const std::vector<Point>& polygon,
                         const Point& point) {
  int n = polygon.size();
  bool inside = false;

  for (int i = 0, j = n - 1; i < n; j = i++) {
    if (((polygon[i].y > point.y) != (polygon[j].y > point.y)) &&
        (point.x < (polygon[j].x - polygon[i].x) * (point.y - polygon[i].y) /
        (polygon[j].y - polygon[i].y) + polygon[i].x)) {
      inside = !inside;
    }
  }

  return inside;
}

int main() {
  std::vector<Point> polygon{{-1, -1}, {1, -1}, {2, 1}, {0, 2}, {-2, 1}};
  Point point{-2, 2};
  std::cout << (is_point_in_polygon(polygon, point) ? "YES" : "NO") << '\n';
}
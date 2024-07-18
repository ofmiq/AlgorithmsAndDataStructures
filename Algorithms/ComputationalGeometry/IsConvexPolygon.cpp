#include <iostream>
#include <vector>

struct Point {
  double x;
  double y;
};

double CrossProduct(const Point& O, const Point& A, const Point& B) {
  return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

bool IsConvex(const std::vector<Point>& points) {
  int n = points.size();
  if (n < 3) {
    return false;
  }

  bool is_positive = false;
  bool is_negative = false;

  for (int i = 0; i < n; ++i) {
    double cross =
        CrossProduct(points[i], points[(i + 1) % n], points[(i + 2) % n]);
    if (cross > 0) {
      is_positive = true;
    } else if (cross < 0) {
      is_negative = true;
    }

    if (is_positive && is_negative) {
      return false;
    }
  }

  return true;
}

int main() {
  std::vector<Point> convex_polygon = {{0, 4},  {4, 2},   {4, -2},
                                       {0, -4}, {-4, -2}, {-4, 2}};
  std::vector<Point> concave_polygon = {{0, 4}, {2, 1},   {4, -2},
                                        {0, 0}, {-4, -2}, {-2, 1}};

  std::cout << std::boolalpha;
  std::cout << "first polygon: " << IsConvex(convex_polygon) << '\n';
  std::cout << "second polygon: " << IsConvex(concave_polygon) << '\n';
}
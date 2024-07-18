#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

struct Point {
  double x;
  double y;
};

double CrossProduct(const Point& O, const Point& A, const Point& B) {
  return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

bool IsPointInTriangle(const Point& p, const Point& p0, const Point& p1,
                       const Point& p2) {
  double d1 = CrossProduct(p, p0, p1);
  double d2 = CrossProduct(p, p1, p2);
  double d3 = CrossProduct(p, p2, p0);
  bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
  bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);
  return !(has_neg && has_pos);
}

bool IsPointInPolygon(const std::vector<Point>& polygon, const Point& p) {
  int n = polygon.size();
  if (n < 3) {
    return false;
  }

  Point p0 = polygon[0];
  std::vector<Point> sorted_points(polygon.begin() + 1, polygon.end());
  std::sort(sorted_points.begin(), sorted_points.end(),
            [&](const Point& a, const Point& b) {
              double angleA = std::atan2(a.y - p0.y, a.x - p0.x);
              double angleB = std::atan2(b.y - p0.y, b.x - p0.x);
              return angleA < angleB;
            });

  int left = 0;
  int right = n - 2;

  while (right - left > 1) {
    int mid = left + (right - left) / 2;
    if (CrossProduct(p0, sorted_points[left], p) *
            CrossProduct(p0, sorted_points[mid], p) >
        0) {
      left = mid;
    } else {
      right = mid;
    }
  }

  return IsPointInTriangle(p, p0, sorted_points[left], sorted_points[right]);
}

int main() {
  std::vector<Point> convex_polygon = {
      {0, 3}, {-1, -2}, {-3, -4}, {-5, 1}, {-3, 3}};
  Point A = {-3, 1};
  Point B = {0, 0};
  std::cout << "is A in polygon: "
            << (IsPointInPolygon(convex_polygon, A) ? "YES" : "NO") << '\n';
  std::cout << "is B in polygon: "
            << (IsPointInPolygon(convex_polygon, B) ? "YES" : "NO") << '\n';
}

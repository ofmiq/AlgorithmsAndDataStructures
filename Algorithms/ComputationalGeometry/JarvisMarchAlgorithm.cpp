#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
  double x;
  double y;
};

double CrossProduct(const Point& O, const Point& A, const Point& B) {
  return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

std::vector<Point> ConvexHullJarvis(const std::vector<Point>& points) {
  int n = points.size();
  if (n < 3) {
    return {};
  }

  std::vector<Point> hull;

  int leftmost = 0;
  for (int i = 1; i < n; ++i) {
    if (points[i].x < points[leftmost].x) {
      leftmost = i;
    }
  }

  int p = leftmost;
  int q;
  while (true) {
    hull.push_back(points[p]);
    q = (p + 1) % n;
    for (int i = 0; i < n; ++i) {
      if (CrossProduct(points[p], points[i], points[q]) > 0) {
        q = i;
      }
    }
    p = q;
    if (p == leftmost) {
      break;
    }
  }

  return hull;
}

int main() {
  std::vector<Point> points = {{2, 1},  {-1, 4}, {0, 0}, {-2, 1},
                               {-3, 0}, {1, 3},  {0, 2}, {-2, 3}};
  std::vector<Point> convex_hull = ConvexHullJarvis(points);

  std::cout << "Points of convex hull: " << '\n';
  for (Point elem : convex_hull) {
    std::cout << elem.x << ' ' << elem.y << '\n';
  }
}
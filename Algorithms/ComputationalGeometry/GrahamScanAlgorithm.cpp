#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

struct Point {
  double x;
  double y;
};

double CrossProduct(const Point& O, const Point& A, const Point& B) {
  return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

std::vector<Point> ConvexHullGraham(std::vector<Point>& points) {
  int n = points.size();
  if (n < 3) {
    return {};
  }

  std::vector<Point> hull;

  Point p0 = *std::min_element(points.begin(), points.end(),
                               [](const Point& a, const Point& b) {
                                 return a.y < b.y || (a.y == b.y && a.x < b.x);
                               });

  std::sort(points.begin(), points.end(), [&](const Point& a, const Point& b) {
    double cp = CrossProduct(p0, a, b);
    if (cp == 0) {
      return (p0.x - a.x) * (p0.x - a.x) + (p0.y - a.y) * (p0.y - a.y) <
             (p0.x - b.x) * (p0.x - b.x) + (p0.y - b.y) * (p0.y - b.y);
    }
    return cp > 0;
  });

  std::stack<Point> S;
  S.push(points[0]);
  S.push(points[1]);

  for (int i = 2; i < n; ++i) {
    while (S.size() > 1) {
      Point top = S.top();
      S.pop();
      Point next_to_top = S.top();
      if (CrossProduct(next_to_top, top, points[i]) > 0) {
        S.push(top);
        break;
      }
    }
    S.push(points[i]);
  }

  while (!S.empty()) {
    hull.push_back(S.top());
    S.pop();
  }

  return hull;
}

int main() {
  std::vector<Point> points = {{2, 1},  {-1, 4}, {0, 0}, {-2, 1},
                               {-3, 0}, {1, 3},  {0, 2}, {-2, 3}};
  std::vector<Point> convex_hull = ConvexHullGraham(points);

  std::cout << "Points of convex hull: " << '\n';
  for (Point elem : convex_hull) {
    std::cout << elem.x << ' ' << elem.y << '\n';
  }
}
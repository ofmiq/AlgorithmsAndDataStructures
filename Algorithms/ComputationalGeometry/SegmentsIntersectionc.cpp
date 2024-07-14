#include <algorithm>
#include <cstdint>
#include <iostream>

struct Point {
  int64_t x;
  int64_t y;
};

struct Segment {
  Point a;
  Point b;
};

struct Vector {
  int64_t x;
  int64_t y;

  Vector operator-(const Vector& other) const {
    return {x - other.x, y - other.y};
  }

  int64_t cross(const Vector& other) const { return x * other.y - y * other.x; }

  int64_t dot(const Vector& other) const { return x * other.x + y * other.y; }
};

Vector to_vector(const Point& a, const Point& b) {
  return {b.x - a.x, b.y - a.y};
}

Vector negate(const Vector& v) { return {-v.x, -v.y}; }

bool on_segment(const Point& p, const Segment& s) {
  return std::min(s.a.x, s.b.x) <= p.x && p.x <= std::max(s.a.x, s.b.x) &&
         std::min(s.a.y, s.b.y) <= p.y && p.y <= std::max(s.a.y, s.b.y);
}

bool segments_intersect(const Segment& s1, const Segment& s2) {
  Vector A = to_vector(s1.a, s1.b);
  Vector B = to_vector(s2.a, s2.b);
  Vector C = to_vector(s1.a, s2.a);
  Vector D = to_vector(s1.a, s2.b);

  int64_t cross1 = A.cross(C);
  int64_t cross2 = A.cross(D);
  int64_t cross3 = B.cross(negate(C));
  int64_t cross4 = B.cross(to_vector(s2.a, s1.b));

  if (cross1 * cross2 < 0 && cross3 * cross4 < 0) {
    return true;
  }

  return (cross1 == 0 && on_segment(s2.a, s1)) ||
         (cross2 == 0 && on_segment(s2.b, s1)) ||
         (cross3 == 0 && on_segment(s1.a, s2)) ||
         (cross4 == 0 && on_segment(s1.b, s2));
}
int main() {
  Segment s1 = {{0, 0}, {5, 5}};
  Segment s2 = {{0, 5}, {5, 0}};

  std::cout << (segments_intersect(s1, s2) ? "YES" : "NO") << '\n';
}

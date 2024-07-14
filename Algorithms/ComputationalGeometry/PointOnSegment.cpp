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

bool is_point_on_segment(const Segment& segment, const Point& point) {
  Vector AP = to_vector(segment.a, point);
  Vector PB = to_vector(point, segment.b);

  return (AP.cross(PB) == 0 && AP.dot(PB) >= 0);
}

int main() {
  Segment s{{0, 0}, {0, 5}};
  Point p{0, 3};
  std::cout << std::boolalpha << is_point_on_segment(s, p) << '\n';
}

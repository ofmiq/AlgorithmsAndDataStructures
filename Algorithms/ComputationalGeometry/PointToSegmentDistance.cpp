#include <cmath>
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

  double modulus() const { return std::sqrt(x * x + y * y); }
};

Vector to_vector(const Point& a, const Point& b) {
  return {b.x - a.x, b.y - a.y};
}

double distance_to_segment(const Segment& segment, const Point& point) {
  Vector AP = to_vector(segment.a, point);
  Vector AB = to_vector(segment.a, segment.b);
  Vector BP = to_vector(segment.b, point);
  Vector BA = to_vector(segment.b, segment.a);

  int64_t dotAP_AB = AP.dot(AB);
  int64_t dotBP_BA = BP.dot(BA);

  if (dotAP_AB <= 0) {
    return AP.modulus();
  } else if (dotBP_BA <= 0) {
    return BP.modulus();
  } else {
    int64_t crossAP_AB = AP.cross(AB);
    return std::abs(crossAP_AB) / AB.modulus();
  }
}

int main() {
  Point point = {2, 3};
  Segment segment = {{0, 0}, {4, 0}};

  double distance = distance_to_segment(segment, point);
  std::cout << distance << '\n';
}

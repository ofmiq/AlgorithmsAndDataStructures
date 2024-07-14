#include <cstdint>
#include <iostream>

struct Point {
  int64_t x;
  int64_t y;
};

struct Vector {
  int64_t x;
  int64_t y;

  Vector operator-(const Vector& other) { return {x - other.x, y - other.y}; }

  int64_t cross(const Vector& other) { return x * other.y - y * other.x; }

  int64_t scalar(const Vector& other) { return x * other.x + y * other.y; }
};

struct Ray {
  Point p;
  Vector v;
};

Vector to_vector(Point a, Point b) { return {b.x - a.x, b.y - a.y}; }

bool is_point_on_ray(Ray ray, Point point) {
  Vector vector = to_vector(ray.p, point);
  int64_t scalar_product = ray.v.scalar(vector);
  int64_t cross_product = ray.v.cross(vector);

  return (scalar_product >= 0 && cross_product == 0);
}

int main() {
  Point p1{0, 0};
  Vector v{3, 2};
  Ray r{p1, v};

  Point p2{6, 4};
  std::cout << std::boolalpha << is_point_on_ray(r, p2) << '\n';
}
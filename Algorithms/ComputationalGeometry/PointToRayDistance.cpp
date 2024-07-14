#include <cmath>
#include <cstdint>
#include <iostream>

struct Point {
  int64_t x;
  int64_t y;
};

struct Vector {
  int64_t x;
  int64_t y;

  Vector operator-(const Vector& other) const {
    return {x - other.x, y - other.y};
  }

  int64_t cross(const Vector& other) const { return x * other.y - y * other.x; }

  int64_t scalar(const Vector& other) const {
    return x * other.x + y * other.y;
  }

  int64_t modulus() const { return std::sqrt(x * x + y * y); }
};

struct Ray {
  Point p;
  Vector v;
};

Vector to_vector(Point a, Point b) { return {b.x - a.x, b.y - a.y}; }

int64_t distance_to_ray(const Ray& ray, const Point& point) {
  Vector vector = to_vector(ray.p, point);
  int64_t scalar_product = ray.v.scalar(vector);

  if (scalar_product > 0) {
    int64_t cross_product = ray.v.cross(vector);
    return std::abs(cross_product) / ray.v.modulus();
  } else {
    return vector.modulus();
  }
}

int main() {
  Point p1{0, 2};
  Vector v{4, 2};
  Ray r{p1, v};

  Point p2{2, 6};
  std::cout << distance_to_ray(r, p2) << '\n';
}

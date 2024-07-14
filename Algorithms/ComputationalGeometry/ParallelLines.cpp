#include <iostream>
#include <cstdint>

struct Line {
  int64_t a;
  int64_t b;
  int64_t c;
};

bool are_parallel(Line line1, Line line2) {
  return (line1.a * line2.b == line2.a * line1.b);
}

int main() {
  Line line1 {2, 3, -6};
  Line line2 {4, 6, -9};
  std::cout << std::boolalpha << are_parallel(line1, line2) << '\n';
}
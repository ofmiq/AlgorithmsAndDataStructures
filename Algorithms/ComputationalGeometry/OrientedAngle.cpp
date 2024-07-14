#include <cmath>
#include <iostream>

double oriented_angle(double angle_ab, double angle_bc) {
  double angle_ac = angle_ab + angle_bc;

  // [-pi, pi]
  while (angle_ac > M_PI) {
    angle_ac -= 2 * M_PI;
  }
  while (angle_ac <= -M_PI) {
    angle_ac += 2 * M_PI;
  }

  return angle_ac;
}

int main() {
  double angle_ab;
  double angle_bc;

  std::cin >> angle_ab >> angle_bc;

  double angle_ac = oriented_angle(angle_ab, angle_bc);

  std::cout << angle_ac << '\n';
}

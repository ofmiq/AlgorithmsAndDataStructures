#include "sorting.h"

int main() {
  std::vector<int> v1 = GenerateRandomVector<int>(8u, 0, 100);
  std::vector<double> v2 = GenerateRandomVector<double>(8u, 0.0, 100.0);

  std::cout << "elem of integer vector:" << '\n';
  for (auto elem : v1) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';

  std::cout << "elem of double vector:" << '\n';
  for (auto elem : v2) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';

  std::cout << "vectors after merge sorting" << '\n';

  std::vector<int> int_result = MergeSort(v1);
  for (auto elem : int_result) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';

  std::vector<double> double_result = MergeSort(v2);
  for (auto elem : double_result) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}
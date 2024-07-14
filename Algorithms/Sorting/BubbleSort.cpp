#include "sorting.h"

void BubbleSort(std::vector<int>& v) {
  bool flag;
  for (size_t i = 0; i < v.size(); ++i) {
    flag = false;
    for (size_t j = 0; j < v.size() - i - 1; ++j) {
      if (v[j] > v[j + 1]) {
        std::swap(v[j], v[j + 1]);
        flag = true;
      }
    }
    if (!flag) {
      break;
    }
  }
}

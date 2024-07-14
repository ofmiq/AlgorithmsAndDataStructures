#include "sorting.h"

void SelectionSort(std::vector<int>& v) {
  for (size_t i = 0; i < v.size() - 1; ++i) {
    int minIndex = i;
    for (size_t j = i + 1; j < v.size(); ++j) {
      if (v[minIndex] > v[j]) {
        minIndex = j;
      }
    }
    std::swap(v[i], v[minIndex]);
  }
}

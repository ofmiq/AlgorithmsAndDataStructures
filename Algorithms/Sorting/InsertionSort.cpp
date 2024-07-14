#include "sorting.h"

void InsertionSort(std::vector<int>& v) {
  for (size_t i = 1; i < v.size(); ++i) {
    int j = i - 1;
    while(j >= 0 && v[j] > v[j + 1]) {
      std::swap(v[j], v[j + 1]);
      j -= 1;
    }
  }
}
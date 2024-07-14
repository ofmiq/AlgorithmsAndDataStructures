#include <iostream>
#include <vector>

#include "sorting.h"

int LomutoPartition(std::vector<int>& arr, int low, int high) {
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; ++j) {
    if (arr[j] < pivot) {
      ++i;
      std::swap(arr[i], arr[j]);
    }
  }
  std::swap(arr[i + 1], arr[high]);
  return i + 1;
}

int HoarePartition(std::vector<int>& arr, int low, int high) {
  int pivot = arr[low];
  int i = low - 1, j = high + 1;

  while (true) {
    do {
      ++i;
    } while (arr[i] < pivot);

    do {
      --j;
    } while (arr[j] > pivot);

    if (i >= j) return j;
    std::swap(arr[i], arr[j]);
  }
}

void ThreeWayPartition(std::vector<int>& arr, int low, int high, int& i,
                       int& j) {
  i = low - 1, j = high;
  int p = low - 1, q = high;
  int pivot = arr[high];

  while (true) {
    while (arr[++i] < pivot);
    while (pivot < arr[--j])
      if (j == low) break;

    if (i >= j) break;

    std::swap(arr[i], arr[j]);

    if (arr[i] == pivot) {
      ++p;
      std::swap(arr[p], arr[i]);
    }

    if (arr[j] == pivot) {
      --q;
      std::swap(arr[j], arr[q]);
    }
  }

  std::swap(arr[i], arr[high]);

  j = i - 1;
  for (int k = low; k < p; k++, j--) {
    std::swap(arr[k], arr[j]);
  }

  i = i + 1;
  for (int k = high - 1; k > q; k--, i++) {
    std::swap(arr[i], arr[k]);
  }
}

template <typename T>
void QuickSort(std::vector<T>& vec, int low, int high) {
  if (low < high) {
    int pi = LomutoPartition(vec, low, high);

    QuickSort(vec, low, pi - 1);
    QuickSort(vec, pi + 1, high);
  }
}

int main() {
  std::vector<int> v = GenerateRandomVector<int>(12);

  for (auto& elem : v) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';

  QuickSort<int>(v, 0, v.size());

  for (auto& elem : v) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}
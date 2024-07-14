#include <iostream>
#include <vector>

#include "sorting.h"

template <typename T>
void SiftDown(std::vector<T>& heap, int start, int end) {
  int root = start;

  while (2 * root + 1 <= end) {
    int child = 2 * root + 1;
    int swap = root;

    if (heap[swap] < heap[child]) {
      swap = child;
    }
    if (child + 1 <= end && heap[swap] < heap[child + 1]) {
      swap = child + 1;
    }
    if (swap == root) {
      return;
    } else {
      std::swap(heap[root], heap[swap]);
      root = swap;
    }
  }
}

template <typename T>
void SiftUp(std::vector<T>& heap, int start) {
  int child = start;

  while (child > 0) {
    int parent = (child - 1) / 2;

    if (heap[parent] < heap[child]) {
      std::swap(heap[parent], heap[child]);
      child = parent;
    } else {
      return;
    }
  }
}

template <typename T>
void BuildHeap(std::vector<T>& vec, int n) {
  for (int i = n / 2 - 1; i >= 0; i--) {
    SiftDown(vec, i, n - 1);
  }
}

template <typename T>
void HeapSort(std::vector<T>& vec) {
  int n = vec.size();

  BuildHeap(vec, n);

  for (int i = n - 1; i > 0; i--) {
    std::swap(vec[0], vec[i]);
    SiftDown(vec, 0, i - 1);
  }
}

int main() {
  std::vector<int> v = GenerateRandomVector<int>(12);
  for (auto& elem : v) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';

  HeapSort(v);
  for (auto& elem : v) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}
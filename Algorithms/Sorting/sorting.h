#ifndef SORTING_H
#define SORTING_H

#include <iostream>
#include <random>
#include <type_traits>
#include <vector>

template <typename T>
std::vector<T> GenerateRandomVector(size_t size, T min_val = 0,
                                    T max_val = 100) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::vector<T> vec;
  vec.reserve(size);

  if constexpr (std::is_integral_v<T>) {
    std::uniform_int_distribution<T> dis(min_val, max_val);
    for (size_t i = 0; i < size; ++i) {
      vec.push_back(dis(gen));
    }
  } else if constexpr (std::is_floating_point_v<T>) {
    std::uniform_real_distribution<T> dis(min_val, max_val);
    for (size_t i = 0; i < size; ++i) {
      vec.push_back(dis(gen));
    }
  }

  return vec;
}

template <typename T>
std::vector<T> Merge(const std::vector<T>& v1, const std::vector<T>& v2) {
  std::vector<T> result;
  result.reserve(v1.size() + v2.size());

  auto it1 = v1.begin();
  auto it2 = v2.begin();

  while (it1 != v1.end() && it2 != v2.end()) {
    if (*it1 < *it2) {
      result.push_back(*it1);
      ++it1;
    } else {
      result.push_back(*it2);
      ++it2;
    }
  }

  result.insert(result.end(), it1, v1.end());
  result.insert(result.end(), it2, v2.end());

  return result;
}

template <typename T>
std::vector<T> MergeSort(const std::vector<T>& vec) {
  if (vec.size() <= 1) {
    return vec;
  }

  size_t mid = vec.size() / 2;
  std::vector<T> left(vec.begin(), vec.begin() + mid);
  std::vector<T> right(vec.begin() + mid, vec.end());

  left = MergeSort(left);
  right = MergeSort(right);

  return Merge(left, right);
}

void SelectionSort(std::vector<int>& v);
void InsertionSort(std::vector<int>& v);
void BubbleSort(std::vector<int>& v);

#endif  // SORTING_H
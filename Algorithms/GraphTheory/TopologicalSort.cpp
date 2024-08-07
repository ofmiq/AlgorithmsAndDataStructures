#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

enum COLOURS { BLACK, GRAY, WHITE };
const int INF = INT_MAX;

// DFS for matrix
bool TopSortDFS_matrix(const std::vector<std::vector<int>>& G, int v,
                       std::vector<COLOURS>& colours,
                       std::vector<int>& sorted) {
  int n = G.size();
  colours[v] = GRAY;
  for (int i = 0; i < n; ++i) {
    if (G[v][i]) {
      if (colours[i] == GRAY) {
        return false;  // Cycle detected
      }
      if (colours[i] == WHITE) {
        if (!TopSortDFS_matrix(G, i, colours, sorted)) {
          return false;
        }
      }
    }
  }
  colours[v] = BLACK;
  sorted.push_back(v);
  return true;
}

std::vector<int> TopologicalSort_matrix(
    const std::vector<std::vector<int>>& G) {
  int n = G.size();
  std::vector<COLOURS> colours(n, WHITE);
  std::vector<int> sorted;
  for (int i = 0; i < n; ++i) {
    if (colours[i] == WHITE) {
      if (!TopSortDFS_matrix(G, i, colours, sorted)) {
        return {};  // Cycle detected
      }
    }
  }
  std::reverse(sorted.begin(), sorted.end());
  return sorted;
}

// DFS for list
bool TopSortDFS_list(const std::vector<std::vector<int>>& G, int v,
                     std::vector<COLOURS>& colours, std::vector<int>& sorted) {
  colours[v] = GRAY;
  for (const int& u : G[v]) {
    if (colours[u] == GRAY) {
      return false;  // Cycle detected
    }
    if (colours[u] == WHITE) {
      if (!TopSortDFS_list(G, u, colours, sorted)) {
        return false;
      }
    }
  }
  colours[v] = BLACK;
  sorted.push_back(v);
  return true;
}

std::vector<int> TopologicalSort_list(const std::vector<std::vector<int>>& G) {
  int n = G.size();
  std::vector<COLOURS> colours(n, WHITE);
  std::vector<int> sorted;
  for (int i = 0; i < n; ++i) {
    if (colours[i] == WHITE) {
      if (!TopSortDFS_list(G, i, colours, sorted)) {
        return {};  // Cycle detected
      }
    }
  }
  std::reverse(sorted.begin(), sorted.end());
  return sorted;
}

int main() {
  // Using adjacency matrix for topological sort
  std::vector<std::vector<int>> adjacency_matrix{
      {0, 0, 0, 0, 1, 0, 0, 0}, 
      {0, 0, 0, 1, 0, 1, 1, 0},
      {0, 0, 0, 0, 0, 0, 0, 0}, 
      {0, 0, 0, 0, 0, 0, 0, 1},
      {0, 0, 0, 0, 0, 0, 0, 1}, 
      {0, 0, 0, 0, 0, 0, 1, 1},
      {0, 0, 0, 0, 0, 0, 0, 0}, 
      {0, 0, 0, 0, 0, 0, 0, 0}
  };

  std::vector<int> matrix_result = TopologicalSort_matrix(adjacency_matrix);

  if (!matrix_result.empty()) {
    std::cout << "Topological Sort (using adjacency matrix): ";
    for (const int& elem : matrix_result) {
      std::cout << elem << ' ';
    }
    std::cout << '\n';
  } else {
    std::cout << "Graph contains a cycle, topological sort not possible (using "
                 "adjacency matrix).\n";
  }

  // Using adjacency list for topological sort
  std::vector<std::vector<int>> adjacency_list{
    {4}, 
    {3, 5, 6}, 
    {}, 
    {7}, 
    {7}, 
    {6, 7},
    {}, 
    {}
  };

  std::vector<int> list_result = TopologicalSort_list(adjacency_list);

  if (!list_result.empty()) {
    std::cout << "Topological Sort (using adjacency list): ";
    for (const int& elem : list_result) {
      std::cout << elem << ' ';
    }
    std::cout << '\n';
  } else {
    std::cout << "Graph contains a cycle, topological sort not possible (using "
                 "adjacency list).\n";
  }

  return 0;
}

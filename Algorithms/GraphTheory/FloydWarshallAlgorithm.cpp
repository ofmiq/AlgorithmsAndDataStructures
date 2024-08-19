#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

const int INF = INT_MAX;

void FloydWarshall(std::vector<std::vector<int>>& G) {
  size_t n = G.size();

  for (size_t k = 0; k < n; ++k) {
    for (size_t u = 0; u < n; ++u) {
      for (size_t v = 0; v < n; ++v) {
        if (G[u][k] != INF && G[k][v] != INF) {
          G[u][v] = std::min(G[u][v], G[u][k] + G[k][v]);
        }
      }
    }
  }

  for (size_t i = 0; i < n; ++i) {
    if (G[i][i] < 0) {
      std::cout << "Negative cycle!\n";
      return;
    }
  }
}

int main() {
  std::vector<std::vector<int>> adjacency_matrix{
      {0, 11, INF, -5, INF, INF, INF},
      {INF, 0, 9, INF, 6, INF, INF},
      {INF, INF, 0, INF, INF, INF, INF},
      {INF, INF, INF, 0, INF, 7, INF},
      {INF, INF, INF, INF, 0, INF, 5},
      {INF, INF, INF, INF, 11, 0, 1},
      {INF, INF, INF, INF, INF, INF, 0},
  };

  FloydWarshall(adjacency_matrix);

  for (const auto& row : adjacency_matrix) {
    for (const auto& elem : row) {
      if (elem == INF) {
        std::cout << "INF ";
      } else {
        std::cout << elem << ' ';
      }
    }
    std::cout << '\n';
  }
}

#include <iostream>
#include <queue>
#include <vector>

std::vector<int> BFS_AdjMatrix(const std::vector<std::vector<int>>& G, int s) {
  int n = G.size();
  std::vector<int> dist(n, -1);
  std::queue<int> q;

  dist[s] = 0;
  q.push(s);

  while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (int u = 0; u < n; ++u) {
      if (G[v][u] && dist[u] == -1) {
        dist[u] = dist[v] + 1;
        q.push(u);
      }
    }
  }

  return dist;
}

std::vector<int> BFS_AdjList(const std::vector<std::vector<int>>& G, int s) {
  int n = G.size();
  std::vector<int> dist(n, -1);
  std::queue<int> q;

  dist[s] = 0;
  q.push(s);

  while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (int u : G[v]) {
      if (dist[u] == -1) {
        dist[u] = dist[v] + 1;
        q.push(u);
      }
    }
  }

  return dist;
}

int main() {
  std::vector<std::vector<int>> adjacency_matrix = {
      {0, 1, 0, 0, 0, 0, 0, 0, 0},
      {1, 0, 1, 0, 0, 1, 0, 0, 0},
      {0, 1, 0, 1, 0, 1, 0, 0, 0},
      {0, 0, 1, 0, 1, 0, 0, 0, 0},
      {0, 0, 0, 1, 0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0, 1, 0, 1, 0},
      {0, 0, 0, 0, 0, 0, 1, 0, 1},
      {0, 0, 0, 0, 0, 0, 0, 1, 0},
  };

  std::vector<std::vector<int>> adjacency_list = {
      {1},
      {0, 2, 5},
      {1, 3, 5},
      {2, 4}, {3},
      {1, 2, 6},
      {5, 7},
      {6, 8},
      {7}
  };

  std::vector<int> result1 = BFS_AdjMatrix(adjacency_matrix, 0);

  for (const auto& elem : result1) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';

  std::vector<int> result2 = BFS_AdjList(adjacency_list, 0);

  for (const auto& elem : result2) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

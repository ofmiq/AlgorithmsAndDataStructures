#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

const int INF = INT_MAX;

bool DFS(int u, int t, std::vector<std::vector<int>>& G, std::vector<int>& prev,
         std::vector<bool>& visited) {
  visited[u] = true;
  if (u == t) {
    return true;
  }

  for (size_t v = 0; v < G.size(); ++v) {
    if (!visited[v] && G[u][v] > 0) {
      prev[v] = u;
      if (DFS(v, t, G, prev, visited)) {
        return true;
      }
    }
  }
  return false;
}

int FordFulkerson(int s, int t, std::vector<std::vector<int>>& G) {
  size_t n = G.size();
  std::vector<int> prev(n);
  int max_flow = 0;

  while (true) {
    std::vector<bool> visited(n, false);
    if (!DFS(s, t, G, prev, visited)) break;

    int flow = INF;
    for (int v = t; v != s; v = prev[v]) {
      int u = prev[v];
      flow = std::min(flow, G[u][v]);
    }

    for (int v = t; v != s; v = prev[v]) {
      int u = prev[v];
      G[u][v] -= flow;
      G[v][u] += flow;
    }

    max_flow += flow;
  }

  return max_flow;
}

int main() {
  std::vector<std::vector<int>> adjacency_matrix {
    {0, 16, 13, 0, 0, 0},
    {0, 0, 0, 12, 0, 0},
    {0, 4, 0, 0, 14, 0},
    {0, 0, 9, 0, 0, 20},
    {0, 0, 0, 7, 0, 4},
    {0, 0, 0, 0, 0, 0}
  };

  int result = FordFulkerson(0, 5, adjacency_matrix);

  std::cout << result << '\n';
}

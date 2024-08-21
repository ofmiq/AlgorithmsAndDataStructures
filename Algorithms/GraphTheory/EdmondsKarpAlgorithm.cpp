#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

const int INF = INT_MAX;

bool BFS(int s, int t, std::vector<std::vector<int>>& G,
         std::vector<int>& prev) {
  int n = G.size();
  std::vector<bool> visited(n, false);
  std::queue<int> q;
  q.push(s);
  visited[s] = true;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v = 0; v < n; ++v) {
      if (!visited[v] && G[u][v] > 0) {
        prev[v] = u;
        visited[v] = true;
        if (v == t) return true;
        q.push(v);
      }
    }
  }

  return false;
}

int EdmondsKarp(int s, int t, std::vector<std::vector<int>>& G) {
  int n = G.size();
  std::vector<int> prev(n);
  int max_flow = 0;

  while (BFS(s, t, G, prev)) {
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
  std::vector<std::vector<int>> adjacency_matrix{
      {0, 0, 0, 0, 0, 0},
      {10, 0, 0, 0, 0, 0},
      {5, 15, 0, 0, 0, 0},
      {0, 9, 4, 0, 0, 0},
      {0, 0, 8, 15, 0, 0},
      {0, 0, 0, 10, 10, 0}
  };

  int result = EdmondsKarp(5, 0, adjacency_matrix);
  
  std::cout << result << '\n';
}

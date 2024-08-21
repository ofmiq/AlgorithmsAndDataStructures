#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

const int INF = INT_MAX;

bool BFS(int s, int t, std::vector<std::vector<int>>& G,
         std::vector<int>& level) {
  int n = G.size();
  fill(level.begin(), level.end(), -1);
  level[s] = 0;
  std::queue<int> q;
  q.push(s);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v = 0; v < n; ++v) {
      if (level[v] < 0 && G[u][v] > 0) {
        level[v] = level[u] + 1;
        q.push(v);
      }
    }
  }

  return level[t] >= 0;
}

int DFS(int u, int t, int flow, std::vector<std::vector<int>>& G,
        std::vector<int>& level, std::vector<int>& ptr) {
  if (u == t) {
    return flow;
  }

  int n = G.size();
  for (int& i = ptr[u]; i < n; ++i) {
    int v = i;
    if (level[v] == level[u] + 1 && G[u][v] > 0) {
      int df = DFS(v, t, std::min(flow, G[u][v]), G, level, ptr);
      if (df > 0) {
        G[u][v] -= df;
        G[v][u] += df;
        return df;
      }
    }
  }

  return 0;
}

int Dinic(int s, int t, std::vector<std::vector<int>>& G) {
  int n = G.size();
  std::vector<int> level(n);
  int max_flow = 0;

  while (BFS(s, t, G, level)) {
    std::vector<int> ptr(n, 0);
    while (int flow = DFS(s, t, INF, G, level, ptr)) {
      max_flow += flow;
    }
  }

  return max_flow;
}

int main() {
  std::vector<std::vector<int>> adjacency_matrix{
      {0, 16, 13, 0, 0, 0},
      {0, 0, 10, 12, 0, 0},
      {0, 4, 0, 0, 14, 0},
      {0, 0, 9, 0, 0, 20},
      {0, 0, 0, 7, 0, 4},
      {0, 0, 0, 0, 0, 0}
  };

  int result = Dinic(0, 5, adjacency_matrix);

  std::cout << result << '\n';
}

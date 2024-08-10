#include <algorithm>
#include <iostream>
#include <vector>

enum COLOURS { WHITE, GRAY, BLACK };

void DFS(const std::vector<std::vector<int>>& G, int v,
         std::vector<COLOURS>& colours, std::vector<int>& time_in,
         std::vector<int>& time_up, std::vector<std::pair<int, int>>& bridges,
         int& time, int parent = -1) {
  colours[v] = GRAY;
  time_in[v] = time_up[v] = ++time;

  for (int u : G[v]) {
    if (u == parent) {
      continue;
    }
    if (colours[u] == WHITE) {
      DFS(G, u, colours, time_in, time_up, bridges, time, v);
      time_up[v] = std::min(time_up[v], time_up[u]);
      if (time_up[u] > time_in[v]) {
        bridges.push_back({v, u});
      }
    } else {
      time_up[v] = std::min(time_up[v], time_in[u]);
    }
  }

  colours[v] = BLACK;
}

std::vector<std::pair<int, int>> Bridges(
    const std::vector<std::vector<int>>& G) {
  int n = G.size();
  std::vector<COLOURS> colours(n, WHITE);
  std::vector<int> time_in(n, -1);
  std::vector<int> time_up(n, -1);
  std::vector<std::pair<int, int>> bridges;
  int time = 0;

  for (int v = 0; v < n; ++v) {
    if (colours[v] == WHITE) {
      DFS(G, v, colours, time_in, time_up, bridges, time);
    }
  }

  return bridges;
}

int main() {
  std::vector<std::vector<int>> adjacency_list{{1, 2},    {0, 2}, {0, 1, 3},
                                               {2, 4, 5}, {3, 5}, {3, 4}};

  std::vector<std::pair<int, int>> bridges = Bridges(adjacency_list);

  std::cout << "Bridge:\n";
  for (const auto& [u, v] : bridges) {
    std::cout << u << " - " << v << '\n';
  }
}

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

enum COLOURS { WHITE, GRAY, BLACK };

void DFS(const std::vector<std::vector<int>>& G, int v, bool is_root,
         std::vector<COLOURS>& colours, std::vector<int>& time_in,
         std::vector<int>& time_up, std::set<int>& articulation_points,
         int& time) {
  colours[v] = GRAY;
  time_in[v] = time_up[v] = ++time;
  int n_children = 0;

  for (int u : G[v]) {
    if (colours[u] == GRAY) {
      time_up[v] = std::min(time_up[v], time_in[u]);
    } else if (colours[u] == WHITE) {
      ++n_children;
      DFS(G, u, false, colours, time_in, time_up, articulation_points, time);
      time_up[v] = std::min(time_up[v], time_up[u]);
      if (!is_root && time_in[v] <= time_up[u]) {
        articulation_points.insert(v);
      }
    }
  }

  if (is_root && n_children > 1) {
    articulation_points.insert(v);
  }

  colours[v] = BLACK;
}

std::set<int> ArticulationPoints(const std::vector<std::vector<int>>& G) {
  int n = G.size();
  std::vector<COLOURS> colours(n, WHITE);
  std::vector<int> time_in(n, -1);
  std::vector<int> time_up(n, -1);
  std::set<int> articulation_points;
  int time = 0;

  for (int v = 0; v < n; ++v) {
    if (colours[v] == WHITE) {
      DFS(G, v, true, colours, time_in, time_up, articulation_points, time);
    }
  }

  return articulation_points;
}

int main() {
  std::vector<std::vector<int>> adjacency_list{
      {1, 2}, {0, 2}, {0, 3}, {2, 4}, {3}};

  std::set<int> articulation_points = ArticulationPoints(adjacency_list);

  std::cout << "Articulation points: ";
  for (int point : articulation_points) {
    std::cout << point << " ";
  }
  std::cout << '\n';
}

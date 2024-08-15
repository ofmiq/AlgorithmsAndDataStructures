#include <climits>
#include <iostream>
#include <vector>

struct Edge {
  int u, v, weight;
};

bool relax(int u, int v, int weight, std::vector<int>& dist) {
  if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
    dist[v] = dist[u] + weight;
    return true;
  }
  return false;
}

std::vector<int> BellmanFord(int n, const std::vector<Edge>& edges, int start) {
  std::vector<int> dist(n, INT_MAX);
  dist[start] = 0;

  for (int i = 1; i < n; ++i) {
    for (const auto& edge : edges) {
      relax(edge.u, edge.v, edge.weight, dist);
    }
  }

  for (const auto& edge : edges) {
    if (relax(edge.u, edge.v, edge.weight, dist)) {
      std::cerr << "Graph contains negative cycle!\n";
      break;
    }
  }

  return dist;
}

int main() {
  int n = 5;
  std::vector<Edge> edges = {{0, 1, 5}, {0, 3, 9},  {1, 2, 7},
                             {1, 4, 7}, {3, 1, -8}, {3, 2, 7}};

  int start = 0;
  std::vector<int> result = BellmanFord(n, edges, start);

  for (size_t i = 0; i < result.size(); ++i) {
    if (result[i] == INT_MAX) {
      std::cout << "Distance to " << i << ": INF\n";
    } else {
      std::cout << "Distance to " << i << ": " << result[i] << '\n';
    }
  }
}

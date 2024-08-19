#include <climits>
#include <iostream>
#include <queue>
#include <vector>

const int INF = INT_MAX;

struct Edge {
  int u, v, weight;
};

bool relax(int u, int v, int weight, std::vector<int>& dist) {
  if (dist[u] != INF && dist[u] + weight < dist[v]) {
    dist[v] = dist[u] + weight;
    return true;
  }
  return false;
}

std::vector<int> BellmanFord(int n, const std::vector<Edge>& edges, int start) {
  std::vector<int> dist(n, INF);
  dist[start] = 0;

  for (int i = 1; i < n; ++i) {
    for (const auto& edge : edges) {
      relax(edge.u, edge.v, edge.weight, dist);
    }
  }

  for (const auto& edge : edges) {
    if (relax(edge.u, edge.v, edge.weight, dist)) {
      std::cerr << "Graph contains negative cycle!\n";
      return {};
    }
  }

  return dist;
}

std::vector<int> Dijkstra(
    const std::vector<std::vector<std::pair<int, int>>>& graph, int start) {
  size_t n = graph.size();
  std::vector<int> dist(n, INF);
  dist[start] = 0;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<>>
      heap;
  heap.push({0, start});

  while (!heap.empty()) {
    int d = heap.top().first;
    int u = heap.top().second;
    heap.pop();

    if (d > dist[u]) continue;

    for (const auto& [v, weight] : graph[u]) {
      if (dist[u] != INF && dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        heap.push({dist[v], v});
      }
    }
  }

  return dist;
}

std::vector<std::vector<int>> Johnson(int n, std::vector<Edge>& edges) {
  std::vector<Edge> newEdges = edges;
  for (int i = 0; i < n; ++i) {
    newEdges.push_back({n, i, 0});
  }

  std::vector<int> h = BellmanFord(n + 1, newEdges, n);
  if (h.empty()) {
    std::cerr << "Graph contains negative cycle!\n";
    return {};
  }

  for (auto& edge : edges) {
    edge.weight += h[edge.u] - h[edge.v];
  }

  std::vector<std::vector<int>> shortestPaths(n, std::vector<int>(n, INF));
  std::vector<std::vector<std::pair<int, int>>> adj(n);

  for (const auto& edge : edges) {
    adj[edge.u].emplace_back(edge.v, edge.weight);
  }

  for (int u = 0; u < n; ++u) {
    std::vector<int> dist = Dijkstra(adj, u);
    for (int v = 0; v < n; ++v) {
      if (dist[v] != INF) {
        shortestPaths[u][v] = dist[v] + h[v] - h[u];
      }
    }
  }

  return shortestPaths;
}

int main() {
  int n = 5;
  std::vector<Edge> edges = {{0, 1, 3},  {0, 2, 8}, {0, 4, -4},
                             {1, 3, 1},  {1, 4, 7}, {2, 1, 4},
                             {3, 2, -5}, {3, 0, 2}, {4, 3, 6}};

  std::vector<std::vector<int>> shortestPaths = Johnson(n, edges);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (shortestPaths[i][j] == INF) {
        std::cout << "INF ";
      } else {
        std::cout << shortestPaths[i][j] << ' ';
      }
    }
    std::cout << '\n';
  }
}

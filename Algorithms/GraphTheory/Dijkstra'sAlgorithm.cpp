#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

int INF = INT_MAX;

struct Edge {
  int vertex, weight;
  bool operator>(const Edge& other) const { return weight > other.weight; }
};

// implementation with a heap (E*logV)
std::vector<int> Dijkstra_heap(const std::vector<std::vector<Edge>>& graph,
                               int start) {
  size_t n = graph.size();
  std::vector<int> dist(n, INF);
  std::vector<int> prev(n, -1);
  dist[start] = 0;
  std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> heap;
  heap.push({start, 0});
  while (!heap.empty()) {
    int u = heap.top().vertex;
    heap.pop();
    for (const Edge& edge : graph[u]) {
      int v = edge.vertex;
      int w = edge.weight;
      if (dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        prev[v] = u;
        heap.push({v, dist[v]});
      }
    }
  }

  return dist;
}

// Implementation with a vector (V^2)
std::vector<int> Dijkstra_vector(const std::vector<std::vector<Edge>>& graph,
                                 int start) {
  size_t n = graph.size();
  std::vector<int> dist(n, INF);
  std::vector<int> prev(n, -1);
  std::unordered_set<int> S;
  dist[start] = 0;

  while (S.size() != n) {
    int u = -1;
    for (size_t i = 0; i < n; ++i) {
      if (S.find(i) == S.end() && (u == -1 || dist[i] < dist[u])) {
        u = i;
      }
    }

    if (u == -1 || dist[u] == INF) break;

    S.insert(u);

    for (const Edge& edge : graph[u]) {
      int v = edge.vertex;
      int w = edge.weight;
      if (dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        prev[v] = u;
      }
    }
  }
  return dist;
}

int main() {
  std::vector<std::vector<Edge>> graph = {{{1, 6}, {2, 10}},
                                          {{0, 6}, {2, 12}, {3, 11}, {4, 14}},
                                          {{0, 10}, {1, 12}, {3, 12}},
                                          {{1, 11}, {2, 12}, {5, 6}},
                                          {{1, 14}, {5, 4}, {6, 6}},
                                          {{3, 6}, {4, 4}, {6, 12}},
                                          {{4, 6}, {5, 12}}};

  int start = 0;

  std::vector<int> result = Dijkstra_heap(graph, start);

  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << "Distance to " << i << ": " << result[i] << '\n';
  }
}

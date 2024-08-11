#include <iostream>
#include <climits>
#include <queue>
#include <vector>
#include <utility>

const int INF = INT_MAX;

struct Edge {
  int weight, vertex;
  bool operator>(const Edge& other) const { return weight > other.weight; }
};

std::vector<int> Prim(const std::vector<std::vector<std::pair<int, int>>>& G) {
  int n = G.size();
  std::vector<int> dist(n, INF);
  std::vector<int> prev(n, -1);
  std::vector<bool> in_mst(n, false);
  std::vector<int> mst_vertices;

  std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> heap;
  dist[0] = 0;
  heap.push({0, 0});

  while (!heap.empty()) {
    int v = heap.top().vertex;
    heap.pop();

    if (in_mst[v]) {
      continue;
    }

    in_mst[v] = true;
    mst_vertices.push_back(v);

    for (const auto& neighbor : G[v]) {
      int u = neighbor.second;
      int weight = neighbor.first;

      if (!in_mst[u] && weight < dist[u]) {
        dist[u] = weight;
        prev[u] = v;
        heap.push({dist[u], u});
      }
    }
  }

  return mst_vertices;
}

int main() {
  std::vector<std::vector<std::pair<int, int>>> G = {
      {{1, 1}, {7, 2}},
      {{1, 0}, {5, 2}, {4, 3}},
      {{7, 0}, {5, 1}, {6, 3}, {3, 4}},
      {{4, 1}, {6, 2}, {2, 4}},
      {{3, 2}, {2, 3}}
  };

  std::vector<int> mst = Prim(G);

  for (const int& elem : mst) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

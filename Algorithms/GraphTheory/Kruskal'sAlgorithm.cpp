#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int u, v, weight;
  bool operator<(const Edge& other) const { return weight < other.weight; }
};

class DSU {
 public:
  DSU(int n) : parent(n), rank(n, 0) {
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  int find(int u) {
    if (u != parent[u]) {
      parent[u] = find(parent[u]);
    }
    return parent[u];
  }

  bool unite(int u, int v) {
    u = find(u);
    v = find(v);

    if (u == v) {
      return false;
    }

    if (rank[u] < rank[v]) {
      std::swap(u, v);
    }

    parent[v] = u;

    if (rank[u] == rank[v]) {
      ++rank[u];
    }

    return true;
  }

 private:
  std::vector<int> parent;
  std::vector<int> rank;
};

std::vector<Edge> Kruskal(int vertices, std::vector<Edge> graph) {
  DSU dsu(vertices);
  std::vector<Edge> mst;
  std::sort(graph.begin(), graph.end());

  for (const auto& edge : graph) {
    if (dsu.unite(edge.u, edge.v)) {
      mst.push_back(edge);
    }
  }

  return mst;
}

int main() {
  int vertices = 7;

  std::vector<Edge> graph{
      {0, 1, 3}, {0, 2, 5}, {1, 3, 7}, {1, 5, 11},
      {1, 6, 4}, {2, 3, 1}, {3, 4, 8}, {3, 5, 7},
  };

  std::vector<Edge> result = Kruskal(vertices, graph);

  if (result.size() != vertices - 1) {
    std::cout << "NON-CONNECTED" << '\n';
    return 0;
  }

  for (const auto& elem : result) {
    std::cout << elem.u << ' ' << elem.v << ' ' << elem.weight << '\n';
  }
}

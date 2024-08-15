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

std::vector<Edge> Boruvka(int vertices, std::vector<Edge>& graph) {
  DSU dsu(vertices);
  std::vector<Edge> mst;

  int components = vertices;

  while (components > 1) {
    std::vector<int> min_edge(vertices, -1);

    for (const auto& edge : graph) {
      int set_u = dsu.find(edge.u);
      int set_v = dsu.find(edge.v);

      if (set_u != set_v) {
        if (min_edge[set_u] == -1 ||
            graph[min_edge[set_u]].weight > edge.weight) {
          min_edge[set_u] = &edge - &graph[0];
        }
        if (min_edge[set_v] == -1 ||
            graph[min_edge[set_v]].weight > edge.weight) {
          min_edge[set_v] = &edge - &graph[0];
        }
      }
    }

    for (int i = 0; i < vertices; ++i) {
      if (min_edge[i] != -1) {
        const Edge& edge = graph[min_edge[i]];
        if (dsu.unite(edge.u, edge.v)) {
          mst.push_back(edge);
          --components;
        }
      }
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

  std::vector<Edge> mst = Boruvka(vertices, graph);

  if (mst.size() != vertices - 1) {
    std::cout << "NON-CONNECTED" << '\n';
  } else {
    for (const auto& edge : mst) {
      std::cout << edge.u << ' ' << edge.v << ' ' << edge.weight << '\n';
    }
  }
}

#include <algorithm>
#include <iostream>
#include <vector>

enum COLOURS { WHITE, GRAY, BLACK };

std::vector<std::vector<int>> TransposeGraph(
    const std::vector<std::vector<int>>& G) {
  int n = G.size();
  std::vector<std::vector<int>> transposed(n);
  for (int v = 0; v < n; ++v) {
    for (int u : G[v]) {
      transposed[u].push_back(v);
    }
  }
  return transposed;
}

void DFS(const std::vector<std::vector<int>>& G, int v,
         std::vector<COLOURS>& colours, std::vector<int>& result) {
  colours[v] = GRAY;
  for (int u : G[v]) {
    if (colours[u] == WHITE) {
      DFS(G, u, colours, result);
    }
  }
  colours[v] = BLACK;
  result.push_back(v);
}

std::vector<int> TopSortNoCycles(const std::vector<std::vector<int>>& G) {
  int n = G.size();
  std::vector<COLOURS> colours(n, WHITE);
  std::vector<int> sorted;
  for (int i = 0; i < n; ++i) {
    if (colours[i] == WHITE) {
      DFS(G, i, colours, sorted);
    }
  }
  std::reverse(sorted.begin(), sorted.end());
  return sorted;
}

std::vector<std::vector<int>> DFS_wrapper(
    const std::vector<std::vector<int>>& G, const std::vector<int>& order) {
  int n = G.size();
  std::vector<COLOURS> colours(n, WHITE);
  std::vector<std::vector<int>> components;
  for (int v : order) {
    if (colours[v] == WHITE) {
      std::vector<int> component;
      DFS(G, v, colours, component);
      components.push_back(component);
    }
  }
  return components;
}

std::vector<std::vector<int>> SCC(const std::vector<std::vector<int>>& G) {
  std::vector<int> order = TopSortNoCycles(G);
  std::vector<std::vector<int>> transposed_graph = TransposeGraph(G);
  return DFS_wrapper(transposed_graph, order);
}

// Calculates the degree of each vertex in an undirected graph
std::vector<int> DegreeOfVertices(const std::vector<std::vector<int>>& G) {
  std::vector<int> degrees(G.size(), 0);
  for (size_t i = 0; i < G.size(); ++i) {
    degrees[i] = G[i].size();
  }
  return degrees;
}

// Checks if an undirected graph is Eulerian
bool IsEulerianUndirectedGraph(const std::vector<std::vector<int>>& G) {
  std::vector<int> degrees = DegreeOfVertices(G);
  for (int degree : degrees) {
    if (degree % 2 != 0) {
      return false;
    }
  }
  return SCC(G).size() == 1;
}

// Checks if an undirected graph is semi-Eulerian
bool IsSemiEulerianUndirectedGraph(const std::vector<std::vector<int>>& G) {
  int odd_degree_count = 0;
  std::vector<int> degrees = DegreeOfVertices(G);
  for (int degree : degrees) {
    if (degree % 2 != 0) {
      ++odd_degree_count;
    }
  }
  return (odd_degree_count == 2 || odd_degree_count == 0) && SCC(G).size() == 1;
}

// Calculates the in-degree of each vertex in a directed graph
std::vector<int> InDegreeOfVertices(const std::vector<std::vector<int>>& G) {
  int n = G.size();
  std::vector<int> in_degrees(n, 0);
  for (int u = 0; u < n; ++u) {
    for (int v : G[u]) {
      ++in_degrees[v];
    }
  }
  return in_degrees;
}

// Calculates the out-degree of each vertex in a directed graph
std::vector<int> OutDegreeOfVertices(const std::vector<std::vector<int>>& G) {
  std::vector<int> out_degrees(G.size(), 0);
  for (size_t u = 0; u < G.size(); ++u) {
    out_degrees[u] = G[u].size();
  }
  return out_degrees;
}

// Checks if a directed graph is Eulerian
bool IsEulerianOrientedGraph(const std::vector<std::vector<int>>& G) {
  std::vector<int> in_degrees = InDegreeOfVertices(G);
  std::vector<int> out_degrees = OutDegreeOfVertices(G);
  for (size_t i = 0; i < G.size(); ++i) {
    if (in_degrees[i] != out_degrees[i]) {
      return false;
    }
  }
  return SCC(G).size() == 1;
}

// Checks if a directed graph is semi-Eulerian
bool IsSemiEulerianOrientedGraph(const std::vector<std::vector<int>>& G) {
  std::vector<int> in_degrees = InDegreeOfVertices(G);
  std::vector<int> out_degrees = OutDegreeOfVertices(G);

  int in_diff = 0;
  int out_diff = 0;

  for (size_t i = 0; i < G.size(); ++i) {
    if (in_degrees[i] != out_degrees[i]) {
      if (in_degrees[i] == out_degrees[i] + 1) {
        ++in_diff;
      } else if (out_degrees[i] == in_degrees[i] + 1) {
        ++out_diff;
      } else {
        return false;
      }
    }
  }

  return (in_diff == 1 && out_diff == 1) || (in_diff == 0 && out_diff == 0);
}

int main() {
  // Example undirected graph that is Eulerian
  std::vector<std::vector<int>> eulerian_undirected_graph{
      {1, 2, 3, 4},
      {0, 2, 3, 4},
      {0, 1, 3, 4},
      {0, 1, 2, 5},
      {0, 1, 2, 5},
      {3, 4}
  };

  if (IsEulerianUndirectedGraph(eulerian_undirected_graph)) {
    std::cout << "Undirected Graph is Eulerian\n";
  } else {
    std::cout << "Undirected Graph is not Eulerian\n";
  }

  // Example undirected graph that is semi-Eulerian
  std::vector<std::vector<int>> semi_eulerian_undirected_graph{
      {1, 2, 3},
      {0, 3},
      {0, 3},
      {0, 1, 2}
  };

  if (IsSemiEulerianUndirectedGraph(semi_eulerian_undirected_graph)) {
    std::cout << "Undirected Graph is Semi-Eulerian\n";
  } else {
    std::cout << "Undirected Graph is not Semi-Eulerian\n";
  }

  // Example directed graph that is Eulerian
  std::vector<std::vector<int>> eulerian_oriented_graph{
      {1},
      {2},
      {3},
      {4},
      {0}
  };

  if (IsEulerianOrientedGraph(eulerian_oriented_graph)) {
    std::cout << "Oriented Graph is Eulerian\n";
  } else {
    std::cout << "Oriented Graph is not Eulerian\n";
  }

  // Example directed graph that is semi-Eulerian
  std::vector<std::vector<int>> semi_eulerian_oriented_graph{
      {1},
      {3},
      {0},
      {2, 4},
      {}
  };

  if (IsSemiEulerianOrientedGraph(semi_eulerian_oriented_graph)) {
    std::cout << "Oriented Graph is Semi-Eulerian\n";
  } else {
    std::cout << "Oriented Graph is not Semi-Eulerian\n";
  }
}

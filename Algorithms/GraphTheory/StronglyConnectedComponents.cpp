#include <algorithm>
#include <iostream>
#include <vector>

enum COLOURS { WHITE, GRAY, BLACK };

// Transpose the graph represented by an adjacency matrix
std::vector<std::vector<int>> TransposeGraph_matrix(
    const std::vector<std::vector<int>>& G) {
  int n = G.size();
  std::vector<std::vector<int>> transposed(n, std::vector<int>(n, 0));
  for (int v = 0; v < n; ++v) {
    for (int u = 0; u < n; ++u) {
      if (G[v][u]) {
        transposed[u][v] = 1;
      }
    }
  }
  return transposed;
}

// Depth-First Search for adjacency matrix
void DFS_matrix(const std::vector<std::vector<int>>& G, int v,
                std::vector<COLOURS>& colours, std::vector<int>& result) {
  colours[v] = GRAY;
  int n = G.size();
  for (int u = 0; u < n; ++u) {
    if (G[v][u] && colours[u] == WHITE) {
      DFS_matrix(G, u, colours, result);
    }
  }
  colours[v] = BLACK;
  result.push_back(v);
}

// Topological Sort for adjacency matrix
std::vector<int> TopSortNoCycles_matrix(
    const std::vector<std::vector<int>>& G) {
  int n = G.size();
  std::vector<COLOURS> colours(n, WHITE);
  std::vector<int> sorted;
  for (int i = 0; i < n; ++i) {
    if (colours[i] == WHITE) {
      DFS_matrix(G, i, colours, sorted);
    }
  }
  std::reverse(sorted.begin(), sorted.end());
  return sorted;
}

// Depth-First Search wrapper for transposed graph
std::vector<std::vector<int>> DFS_matrix_wrapper(
    const std::vector<std::vector<int>>& G, const std::vector<int>& order) {
  int n = G.size();
  std::vector<COLOURS> colours(n, WHITE);
  std::vector<std::vector<int>> components;
  for (int v : order) {
    if (colours[v] == WHITE) {
      std::vector<int> component;
      DFS_matrix(G, v, colours, component);
      components.push_back(component);
    }
  }
  return components;
}

// Find Strongly Connected Components for adjacency matrix
std::vector<std::vector<int>> SCC_matrix(
    const std::vector<std::vector<int>>& G) {
  std::vector<int> order = TopSortNoCycles_matrix(G);
  std::vector<std::vector<int>> transposed_graph = TransposeGraph_matrix(G);
  return DFS_matrix_wrapper(transposed_graph, order);
}

// Transpose the graph represented by an adjacency list
std::vector<std::vector<int>> TransposeGraph_list(
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

// Depth-First Search for adjacency list
void DFS_list(const std::vector<std::vector<int>>& G, int v,
              std::vector<COLOURS>& colours, std::vector<int>& result) {
  colours[v] = GRAY;
  for (int u : G[v]) {
    if (colours[u] == WHITE) {
      DFS_list(G, u, colours, result);
    }
  }
  colours[v] = BLACK;
  result.push_back(v);
}

// Topological Sort for adjacency list
std::vector<int> TopSortNoCycles_list(const std::vector<std::vector<int>>& G) {
  int n = G.size();
  std::vector<COLOURS> colours(n, WHITE);
  std::vector<int> sorted;
  for (int i = 0; i < n; ++i) {
    if (colours[i] == WHITE) {
      DFS_list(G, i, colours, sorted);
    }
  }
  std::reverse(sorted.begin(), sorted.end());
  return sorted;
}

// Depth-First Search wrapper for transposed graph
std::vector<std::vector<int>> DFS_list_wrapper(
    const std::vector<std::vector<int>>& G, const std::vector<int>& order) {
  int n = G.size();
  std::vector<COLOURS> colours(n, WHITE);
  std::vector<std::vector<int>> components;
  for (int v : order) {
    if (colours[v] == WHITE) {
      std::vector<int> component;
      DFS_list(G, v, colours, component);
      components.push_back(component);
    }
  }
  return components;
}

// Find Strongly Connected Components for adjacency list
std::vector<std::vector<int>> SCC_list(const std::vector<std::vector<int>>& G) {
  std::vector<int> order = TopSortNoCycles_list(G);
  std::vector<std::vector<int>> transposed_graph = TransposeGraph_list(G);
  return DFS_list_wrapper(transposed_graph, order);
}

int main() {
  // Using adjacency matrix for finding SCC
  std::vector<std::vector<int>> adjacency_matrix{
      {0, 1, 0, 0, 1, 0, 0}, 
      {0, 0, 1, 0, 0, 1, 0}, 
      {1, 0, 0, 0, 0, 0, 1},
      {0, 0, 0, 0, 1, 0, 0}, 
      {0, 0, 0, 1, 0, 0, 1}, 
      {0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0}
  };

  std::vector<std::vector<int>> result_matrix = SCC_matrix(adjacency_matrix);

  std::cout << "Strongly Connected Components (matrix):\n";
  for (const auto& component : result_matrix) {
    for (const auto& node : component) {
      std::cout << node << ' ';
    }
    std::cout << '\n';
  }

  // Using adjacency list for finding SCC
  std::vector<std::vector<int>> adjacency_list{
    {1, 4}, 
    {2, 5}, 
    {0, 6}, 
    {4},
    {3, 6}, 
    {},
    {}
  };

  std::vector<std::vector<int>> result_list = SCC_list(adjacency_list);

  std::cout << "Strongly Connected Components (list):\n";
  for (const auto& component : result_list) {
    for (const auto& node : component) {
      std::cout << node << ' ';
    }
    std::cout << '\n';
  }
}

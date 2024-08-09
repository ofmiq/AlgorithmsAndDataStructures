#include <climits>
#include <iostream>
#include <vector>

enum COLOURS { WHITE, GRAY, BLACK };

std::pair<bool, std::vector<int>> IsCyclic_matrix(
    const std::vector<std::vector<int>>& G, int v, int parent,
    std::vector<COLOURS>& colours, std::vector<int>& path) {
  int n = G.size();

  colours[v] = GRAY;
  path.push_back(v);

  for (int i = 0; i < n; ++i) {
    if (G[v][i] && colours[i] == WHITE) {
      auto result = IsCyclic_matrix(G, i, v, colours, path);
      if (result.first) {
        return result;
      }
    } else if (G[v][i] && i != parent && colours[i] == GRAY) {
      path.push_back(i);
      return {true, path};
    }
  }

  colours[v] = BLACK;
  path.pop_back();
  return {false, path};
}

std::pair<bool, std::vector<int>> IsCyclic_matrix_wrapper(
    const std::vector<std::vector<int>>& G, int v) {
  int n = G.size();
  std::vector<COLOURS> colours(n, WHITE);
  std::vector<int> path;

  return IsCyclic_matrix(G, v, -1, colours, path);
}

std::pair<bool, std::vector<int>> IsCyclic_list(
    const std::vector<std::vector<int>>& adjList, int v, int parent,
    std::vector<COLOURS>& colours, std::vector<int>& path) {
  colours[v] = GRAY;
  path.push_back(v);

  for (int u : adjList[v]) {
    if (colours[u] == WHITE) {
      auto result = IsCyclic_list(adjList, u, v, colours, path);
      if (result.first) {
        return result;
      }
    } else if (u != parent && colours[u] == GRAY) {
      path.push_back(u);
      return {true, path};
    }
  }

  colours[v] = BLACK;
  path.pop_back();
  return {false, path};
}

std::pair<bool, std::vector<int>> IsCyclic_list_wrapper(
    const std::vector<std::vector<int>>& adjList, int v) {
  int n = adjList.size();
  std::vector<COLOURS> colours(n, WHITE);
  std::vector<int> path;

  return IsCyclic_list(adjList, v, -1, colours, path);
}

int main() {
  // Using adjacency matrix for undirected graph
  std::vector<std::vector<int>> adjacency_matrix{
      {0, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 0, 0},
      {0, 0, 0, 1, 1, 0, 0, 0}, {0, 1, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 0},
      {0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 1, 0, 0, 0}};

  auto result_matrix = IsCyclic_matrix_wrapper(adjacency_matrix, 0);

  bool is_cyclic_matrix = result_matrix.first;
  std::vector<int> path_matrix = result_matrix.second;

  if (is_cyclic_matrix) {
    std::cout << "Graph has a cycle (using adjacency matrix)!" << '\n';
    std::cout << "Path: ";
    for (const int& elem : path_matrix) {
      std::cout << elem << ' ';
    }
    std::cout << '\n';
  } else {
    std::cout << "Graph has no cycle (using adjacency matrix)!" << '\n';
  }

  // Using adjacency list for undirected graph
  std::vector<std::vector<int>> adjacency_list = {
      {1}, {0, 2, 3, 4}, {1, 3}, {1, 2, 4, 5}, {1, 3},
      {3}, {7, 8},       {6, 8}, {6, 7}};

  auto result_list = IsCyclic_list_wrapper(adjacency_list, 0);

  bool is_cyclic_list = result_list.first;
  std::vector<int> path_list = result_list.second;

  if (is_cyclic_list) {
    std::cout << "Graph has a cycle (using adjacency list)!" << '\n';
    std::cout << "Path: ";
    for (const int& elem : path_list) {
      std::cout << elem << ' ';
    }
    std::cout << '\n';
  } else {
    std::cout << "Graph has no cycle (using adjacency list)!" << '\n';
  }
}

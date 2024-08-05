#include <climits>
#include <iostream>
#include <vector>

enum COLOURS { WHITE, GRAY, BLACK };
const int INF = INT_MAX;

std::pair<int, std::vector<int>> DFS_matrix(
    const std::vector<std::vector<int>>& G, int v,
    std::vector<COLOURS>& colours, std::vector<int>& path) {
  int n = G.size();
  int count = 1;

  colours[v] = GRAY;
  path.push_back(v);

  for (int i = 0; i < n; ++i) {
    if (G[v][i] && colours[i] == WHITE) {
      auto result = DFS_matrix(G, i, colours, path);
      count += result.first;
    }
  }

  colours[v] = BLACK;
  return {count, path};
}

std::pair<int, std::vector<int>> DFS_matrix_wrapper(
    const std::vector<std::vector<int>>& G, int v) {
  int n = G.size();
  std::vector<COLOURS> colours(n, WHITE);
  std::vector<int> path;

  return DFS_matrix(G, v, colours, path);
}

std::pair<int, std::vector<int>> DFS_list(
    const std::vector<std::vector<int>>& adjList, int v,
    std::vector<COLOURS>& colours, std::vector<int>& path) {
  int count = 1;

  colours[v] = GRAY;
  path.push_back(v);

  for (int u : adjList[v]) {
    if (colours[u] == WHITE) {
      auto result = DFS_list(adjList, u, colours, path);
      count += result.first;
    }
  }

  colours[v] = BLACK;
  return {count, path};
}

std::pair<int, std::vector<int>> DFS_list_wrapper(
    const std::vector<std::vector<int>>& adjList, int v) {
  int n = adjList.size();
  std::vector<COLOURS> colours(n, WHITE);
  std::vector<int> path;

  return DFS_list(adjList, v, colours, path);
}

int main() {
  // Using adjacency matrix
  std::vector<std::vector<int>> adjacency_matrix{
      {0, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 0, 0, 0, 0},
      {0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 1, 0}};

  int start_vertex = 0;
  auto result_matrix = DFS_matrix_wrapper(adjacency_matrix, start_vertex);

  int visited_vertex_matrix = result_matrix.first;
  std::vector<int> path_matrix = result_matrix.second;

  std::cout << "Using adjacency matrix:\n";
  std::cout << "Number of vertices in the same component: "
            << visited_vertex_matrix << '\n';
  std::cout << "Path:\n";

  for (const int& elem : path_matrix) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';

  // Using adjacency list
  std::vector<std::vector<int>> adjacency_list = {
      {1}, {2, 3, 4}, {3}, {4, 5}, {}, {}, {7, 8}, {}, {7}};

  auto result_list = DFS_list_wrapper(adjacency_list, start_vertex);

  int visited_vertex_list = result_list.first;
  std::vector<int> path_list = result_list.second;

  std::cout << "Using adjacency list:\n";
  std::cout << "Number of vertices in the same component: "
            << visited_vertex_list << '\n';
  std::cout << "Path:\n";

  for (const int& elem : path_list) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

#include <iostream>
#include <vector>

/*
Черепашка находится в левом верхнем углу прямоугольной сетки размером n x m и
хочет добраться до правого нижнего угла. Черепашка может двигаться только вправо
или вниз на каждой клетке. В каждой клетке находится некоторое количество монет.
Черепашка собирает монеты по пути, и цель состоит в том, чтобы собрать
максимальное количество монет, достигнув конечной точки.

Напишите программу, которая вычисляет максимальное количество монет, которые
черепашка может собрать.
*/

// функция для откладки
void print_grid(int n, int m, const std::vector<std::vector<int>>& grid) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cout << grid[i][j] << ' ';
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

// изначально просчитываем первый столбец и колонку
int turtle(const std::vector<std::vector<int>>& grid) {
  int n = grid.size();
  int m = grid[0].size();

  std::vector<std::vector<int>> dp (n, std::vector<int>(m, 0));
  dp[0][0] = grid[0][0];

  std::cout << "initialization of dp matrix:" << '\n';
  print_grid(n, m, dp);
  
  std::cout << "first cycle: " << '\n';
  for (int i = 1; i < n; ++i) {
    dp[i][0] = dp[i-1][0] + grid[i][0];
    print_grid(n, m, dp);
  }
  
  std::cout << "second cycle: " << '\n';
  for (int j = 1; j < m; ++j) {
    dp[0][j] = dp[0][j-1] + grid[0][j];
    print_grid(n, m, dp);
  }
  
  std::cout << "final cycle: " << '\n';
  for (int i = 1; i < n; ++i) {
    for (int j = 1; j < m; ++j) {
      dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]) + grid[i][j];
      print_grid(n, m, dp);
    }
  }
  
  return dp[n-1][m-1];
}

int main() {
  std::vector<std::vector<int>> grid 
  {
    {1, 3, 1}, 
    {1, 5, 1}, 
    {4, 2, 1}
  };
  std::cout << turtle(grid) << '\n';
}
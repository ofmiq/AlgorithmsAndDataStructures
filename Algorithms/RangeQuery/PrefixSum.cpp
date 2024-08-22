#include <iostream>
#include <vector>

std::vector<int> PrefixSum(const std::vector<int>& array) {
    int n = array.size();
    std::vector<int> prefix_sums(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        prefix_sums[i + 1] = prefix_sums[i] + array[i];
    }

    return prefix_sums;
}

std::vector<std::vector<int>> PrefixSum2D(const std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    std::vector<std::vector<int>> prefix_sum_2d(n + 1, std::vector<int>(m + 1, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            prefix_sum_2d[i + 1][j + 1] = matrix[i][j] + prefix_sum_2d[i][j + 1] 
                                          + prefix_sum_2d[i + 1][j] - prefix_sum_2d[i][j];
        }
    }

    return prefix_sum_2d;
}

void Print1D(const std::vector<int>& array) {
    for (const auto& elem : array) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

void Print2D(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    std::vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> result = PrefixSum(v1);

    std::cout << "1D prefix sum:\n";
    Print1D(result);
    std::cout << '\n';

    std::cout << "Range sum [1; 6):\n";
    std::cout << result[6] - result[1] << '\n' << '\n';

    std::vector<std::vector<int>> v2{
        {1,  2,  3,  4,  5,  6},
        {7,  8,  9, 10, 11, 12},
        {13, 14, 15, 16, 17, 18},
        {19, 20, 21, 22, 23, 24},
        {25, 26, 27, 28, 29, 30},
        {31, 32, 33, 34, 35, 36}
    };

    std::vector<std::vector<int>> result2 = PrefixSum2D(v2);

    std::cout << "2D prefix sum:\n";
    Print2D(result2);
    std::cout << '\n';
    int row1 = 1, col1 = 1, row2 = 4, col2 = 4;
    int range_sum = result2[row2 + 1][col2 + 1] - result2[row1][col2 + 1] -
                    result2[row2 + 1][col1] + result2[row1][col1];

    std::cout << "Range sum (from (1,1) to (4, 4)):\n";
    std::cout << range_sum << '\n';
}

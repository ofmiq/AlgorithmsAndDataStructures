#include <vector>

#include "BST.cpp"

void traversal(Node* node, std::vector<int>& temp) {
  if (node != nullptr) {
    traversal(node->left, temp);
    temp.push_back(node->val);
    traversal(node->right, temp);
  }
}

double FindMedian(const BST& tree) {
  std::vector<int> temp;
  traversal(tree.head, temp);

  int size = temp.size();
  if (size % 2 == 0) {
    return (temp[size / 2 - 1] + temp[size / 2]) / 2.0;
  } else {
    return temp[size / 2];
  }
}

int main() {
  BST tree = {5, 3, 7, 2, 4, 6, 8, 1};
  double result = FindMedian(tree);
  std::cout << result << '\n';
}
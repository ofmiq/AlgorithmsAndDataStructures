#include "BST.cpp"

int CalculateHeight(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  int left_height = CalculateHeight(node->left);
  int right_height = CalculateHeight(node->right);
  return left_height > right_height ? left_height + 1 : right_height + 1;
}

int FindHeight(const BST& tree) { return CalculateHeight(tree.head); }

int main() {
  BST tree = {5, 3, 7, 2, 4, 6, 8, 1};
  std::cout << FindHeight(tree) << '\n';
}
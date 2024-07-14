#include <vector>

#include "BST.cpp"

void GetLeaves(Node* node, std::vector<Node*>& leaves) {
  if (node == nullptr) {
    return;
  }

  if (node->left == nullptr && node->right == nullptr) {
    leaves.push_back(node);
    return;
  }

  GetLeaves(node->left, leaves);
  GetLeaves(node->right, leaves);
}

std::vector<Node*> FindLeavesFromBST(const BST& tree) {
  std::vector<Node*> leaves;
  GetLeaves(tree.head, leaves);
  return leaves;
}

int main() {
  BST tree = {5, 3, 7, 2, 4, 6, 8, 1};
  std::vector<Node*> leaves = FindLeavesFromBST(tree);
  for (auto elem : leaves) {
    std::cout << elem->val << ' ';
  }
  std::cout << '\n';
}

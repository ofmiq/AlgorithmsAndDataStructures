#include <vector>

#include "BST.cpp"

void traversal(Node* node, std::vector<int>& temp) {
  if (node != nullptr) {
    traversal(node->left, temp);
    temp.push_back(node->val);
    traversal(node->right, temp);
  }
}

int CountPairs(const BST& tree1, const BST& tree2, int x) {
  std::vector<int> arr1;
  std::vector<int> arr2;

  traversal(tree1.head, arr1);
  traversal(tree2.head, arr2);

  int count = 0;
  int i = 0;
  int j = arr2.size() - 1;

  while (i < arr1.size() && j >= 0) {
    if (arr1[i] + arr2[j] == x) {
      count++;
      i++;
      j--;
    } else if (arr1[i] + arr2[j] < x) {
      i++;
    } else {
      j--;
    }
  }

  return count;
}

int main() {
  BST tree1 = {5, 3, 7, 2, 4, 6, 8};
  BST tree2 = {10, 6, 15, 3, 8, 11, 18};
  int x = 16;

  int result = CountPairs(tree1, tree2, x);
  std::cout << result << '\n';
}
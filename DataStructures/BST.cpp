#include <iostream>

class BST {
 private:
  struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int val) : val(val), left(nullptr), right(nullptr) {}
  };
  Node* head;

  void insert(Node*& node, int val) {
    if (node == nullptr) {
      node = new Node(val);
    } else if (val < node->val) {
      insert(node->left, val);
    } else {
      insert(node->right, val);
    }
  }

  void remove(Node*& node, int val) {
    if (node == nullptr) {
      return;
    }

    if (val < node->val) {
      remove(node->left, val);
    } else if (val > node->val) {
      remove(node->right, val);
    }

    if (node->left == nullptr && node->right == nullptr) {
      delete node;
      node = nullptr;
    } else if (node->left == nullptr) {
      Node* temp = node;
      node = node->right;
      delete temp;
    } else if (node->right == nullptr) {
      Node* temp = node;
      node = node->left;
      delete temp;
    } else {
      int min = find_min(node->right);
      node->val = min;
      remove(node->right, min);
    }
  }

  bool search(Node* node, int val) const {
    if (node == nullptr) {
      return false;
    }

    if (node->val == val) {
      return true;
    } else if (val < node->val) {
      return search(node->left, val);
    } else {
      return search(node->right, val);
    }
  }

  int find_max(Node* node) const {
    if (node == nullptr) {
      return -1;
    }
    while (node->right != nullptr) {
      node = node->right;
    }
    return node->val;
  }

  int find_min(Node* node) const {
    if (node == nullptr) {
      return -1;
    }
    while (node->left != nullptr) {
      node = node->left;
    }
    return node->val;
  }

  void print_in_order(Node* node) const {
    if (node != nullptr) {
      print_in_order(node->left);
      std::cout << node->val << " ";
      print_in_order(node->right);
    }
  }

  void clear(Node*& node) {
    if (node != nullptr) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

 public:
  BST() : head(nullptr) {}

  BST(std::initializer_list<int> list) : head(nullptr) {
    for (int val : list) {
      insert(val);
    }
  }

  void insert(int val) { insert(head, val); }

  void remove(int val) { remove(head, val); }

  bool is_contain(int val) const { return search(head, val); }

  int max() const { return find_max(head); }

  int min() const { return find_min(head); }

  void print() const { print_in_order(head); }

  ~BST() { clear(head); }
};

int main() {
  BST tree = {5, 3, 7, 2, 4, 6, 8};
  tree.insert(1);
  tree.remove(5);
  std::cout << std::boolalpha << "is 2 in tree? : " << tree.is_contain(2)
            << '\n';
  std::cout << std::boolalpha << "is 0 in tree? : " << tree.is_contain(0)
            << '\n';
  std::cout << "min of tree : " << tree.min() << '\n';
  std::cout << "max of tree : " << tree.max() << '\n';
  tree.print();
  std::cout << '\n';
}

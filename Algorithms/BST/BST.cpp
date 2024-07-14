#include <iostream>

struct Node {
  int val;
  Node* left;
  Node* right;
  Node(int val) : val(val), left(nullptr), right(nullptr) {}
};

struct BST {
  Node* head;

  BST() : head(nullptr) {}

  BST(std::initializer_list<int> list) : head(nullptr) {
    for (int val : list) {
      insert(val);
    }
  }

  void insert(int val) { insert(head, val); }

  void insert(Node*& node, int val) {
    if (node == nullptr) {
      node = new Node(val);
    } else if (val < node->val) {
      insert(node->left, val);
    } else {
      insert(node->right, val);
    }
  }

  void clear(Node*& node) {
    if (node != nullptr) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  ~BST() { clear(head); }
};
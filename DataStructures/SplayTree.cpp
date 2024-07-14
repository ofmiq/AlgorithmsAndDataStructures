#include <iostream>

struct Node {
  int val;
  Node* parent;
  Node* left;
  Node* right;

  Node(int val) : val(val), parent(nullptr), left(nullptr), right(nullptr) {}
};

class SplayTree {
 private:
  Node* head;

  // Helper functions for rotations
  Node* singleRotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent != nullptr) {
      if (x->parent->left == x) {
        x->parent->left = y;
      } else {
        x->parent->right = y;
      }
    } else {
      head = y;
    }
    y->left = x;
    x->parent = y;
    return y;
  }

  Node* singleRotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent != nullptr) {
      if (x->parent->right == x) {
        x->parent->right = y;
      } else {
        x->parent->left = y;
      }
    } else {
      head = y;
    }
    y->right = x;
    x->parent = y;
    return y;
  }

  // Splay operation
  void splay(Node* node) {
    while (node->parent != nullptr) {
      if (node->parent->parent == nullptr) {
        if (node == node->parent->left) {
          singleRotateRight(node->parent);
        } else {
          singleRotateLeft(node->parent);
        }
      } else if (node == node->parent->left &&
                 node->parent == node->parent->parent->left) {
        singleRotateRight(node->parent->parent);
        singleRotateRight(node->parent);
      } else if (node == node->parent->right &&
                 node->parent == node->parent->parent->right) {
        singleRotateLeft(node->parent->parent);
        singleRotateLeft(node->parent);
      } else if (node == node->parent->left &&
                 node->parent == node->parent->parent->right) {
        singleRotateRight(node->parent);
        singleRotateLeft(node->parent);
      } else {
        singleRotateLeft(node->parent);
        singleRotateRight(node->parent);
      }
    }
  }

  // Helper function for delete
  Node* minimum(Node* node) {
    while (node->left != nullptr) {
      node = node->left;
    }
    return node;
  }

  // Helper function for destructor
  void clear(Node*& node) {
    if (node != nullptr) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  // Helper function for print
  void reverseInOrder(Node* node, int indent) {
    if (node != nullptr) {
      indent++;
      reverseInOrder(node->right, indent);

      for (int i = 0; i < indent; i++) {
        std::cout << "  ";
      }
      std::cout << node->val << '\n';

      reverseInOrder(node->left, indent);
    }
  }

 public:
  SplayTree() : head(nullptr) {}

  SplayTree(std::initializer_list<int> list) {
    for (const int& elem : list) {
      insert(elem);
    }
  }

  ~SplayTree() { clear(head); }

  // Search operation
  Node* search(int val) {
    Node* current = head;
    while (current != nullptr) {
      if (val == current->val) {
        splay(current);
        return current;
      } else if (val < current->val) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return nullptr;
  }

  // Insertion operation
  void insert(int val) {
    Node* newNode = new Node(val);
    Node* parent = nullptr;
    Node* current = head;

    while (current != nullptr) {
      parent = current;
      if (val < current->val) {
        current = current->left;
      } else {
        current = current->right;
      }
    }

    newNode->parent = parent;
    if (parent == nullptr) {
      head = newNode;
    } else if (val < parent->val) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }

    splay(newNode);
  }

  // Delete operation
  void deleteNode(int val) {
    Node* nodeToDelete = search(val);
    if (nodeToDelete == nullptr) {
      return;
    }
    splay(nodeToDelete);
    if (nodeToDelete->left == nullptr) {
      head = nodeToDelete->right;
    } else {
      Node* maxNode = nodeToDelete->left;
      while (maxNode->right != nullptr) {
        maxNode = maxNode->right;
      }
      if (nodeToDelete->right != nullptr) {
        nodeToDelete->right->parent = maxNode;
      }
      head = nodeToDelete->left;
      head->parent = nullptr;
      maxNode->right = nodeToDelete->right;
    }
    delete nodeToDelete;
  }

  void print() { reverseInOrder(head, 0); }
};

int main() {
  SplayTree tree{10, 15, 25, 20, 5};

  std::cout << "Initial Tree (Level by Level):\n";
  tree.print();
  std::cout << '\n';

  int valToSearch = 15;
  Node* foundNode = tree.search(valToSearch);
  if (foundNode) {
    std::cout << "Node with val " << valToSearch
              << " found and splayed to the head.\n";
  } else {
    std::cout << "Node with val " << valToSearch << " not found.\n";
  }
  std::cout << "Tree after searching for val " << valToSearch << ":\n";
  tree.print();
  std::cout << '\n';

  int valToInsert = 18;
  std::cout << "Inserting val " << valToInsert << " into the tree.\n";
  tree.insert(valToInsert);
  std::cout << "Tree after insertion:\n";
  tree.print();
  std::cout << '\n';

  int valToDelete = 10;
  std::cout << "Deleting node with val " << valToDelete << " from the tree.\n";
  tree.deleteNode(valToDelete);
  std::cout << "Tree after deletion:\n";
  tree.print();
  std::cout << '\n';
  std::cout << "--------------------------------------" << '\n';
}

#include <iostream>

struct Node {
  int val;
  size_t height;
  Node* left;
  Node* right;
  Node(int val) : val(val), height(1), left(nullptr), right(nullptr) {}
};

class AVL {
 private:
  Node* head;

  size_t get_height(Node* node) { return node ? node->height : 0; }

  int get_balance_factor(Node* node) {
    return get_height(node->right) -
           get_height(node->left);  // normal b-fac: -1, 0, 1
  }

  void fix_height(Node* node) {  // fixed height after balance
    size_t h_left = get_height(node->left);
    size_t h_right = get_height(node->right);
    node->height = (h_left > h_right ? h_left : h_right) + 1;
  }

  Node* rotate_right(Node* p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    fix_height(p);
    fix_height(q);
    return q;
  }

  Node* rotate_left(Node* q) {
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    fix_height(q);
    fix_height(p);
    return p;
  }

  Node* find_min(Node* node) {
    return node->left ? find_min(node->left) : node;
  }

  Node* remove_min(Node* node) {
    if (node->left == nullptr) {
      return node->right;
    }
    node->left = remove_min(node->left);
    return balance(node);
  }

  Node* balance(Node* p) {
    fix_height(p);

    if (get_balance_factor(p) == 2) {
      if (get_balance_factor(p->right) < 0) {  // right-left rotate
        p->right = rotate_right(p->right);
      }
      return rotate_left(p);
    }

    if (get_balance_factor(p) == -2) {
      if (get_balance_factor(p->left) > 0) {  // left-right rotate
        p->left = rotate_left(p->left);
      }
      return rotate_right(p);
    }

    return p;
  }

  Node* insert(Node* node, int val) {
    if (node == nullptr) {
      return new Node(val);
    }

    if (val < node->val) {
      node->left = insert(node->left, val);
    } else {
      node->right = insert(node->right, val);
    }

    return balance(node);
  }

  Node* remove(Node* node, int val) {
    if (node == nullptr) {
      return nullptr;
    }

    if (val < node->val) {
      node->left = remove(node->left, val);
    } else if (val > node->val) {
      node->right = remove(node->right, val);
    } else {  // val == node->val
      Node* left = node->left;
      Node* right = node->right;
      delete node;
      if (right == nullptr) {
        return left;
      }
      Node* min = find_min(right);
      min->right = remove_min(right);
      min->left = left;
      return balance(min);
    }
    return balance(node);
  }

  Node* search(Node* node, int val) {
    if (node == nullptr || node->val == val) {
      return node;
    }
    if (val < node->val) {
      return search(node->left, val);
    } else {
      return search(node->right, val);
    }
  }

  void clear(Node* node) {
    if (node != nullptr) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  void print(Node* root, int space) {
    if (root == nullptr) {
      return;
    }
    space += 10;

    print(root->right, space);
    std::cout << '\n';

    for (int i = 2; i < space; i++) {
      std::cout << " ";
    }

    std::cout << root->val << "\n";

    print(root->left, space);
  }

 public:
  AVL() : head(nullptr) {}

  AVL(std::initializer_list<int> list) : head(nullptr) {
    for (int elem : list) {
      insert(elem);
    }
  }

  ~AVL() { clear(head); }

  void insert(int val) { head = insert(head, val); }

  void remove(int val) { head = remove(head, val); }

  bool is_contain(int val) { return search(head, val) != nullptr; }

  void print() { print(head, 0); }
};

int main() {
  AVL tree{10, 20, 30, 40, 50, 25};

  std::cout << "AVL Tree created with elements: {10, 20, 30, 40, 50, 25}";
  tree.print();

  std::cout << "Searching for 20 in the tree: "
            << (tree.is_contain(20) ? "Found" : "Not Found");
  std::cout << "\nSearching for 15 in the tree: "
            << (tree.is_contain(15) ? "Found" : "Not Found") << '\n';

  tree.insert(15);
  std::cout << "Inserted 15 into the tree.\n";
  tree.print();
  std::cout << "Searching for 15 in the tree: "
            << (tree.is_contain(15) ? "Found" : "Not Found") << '\n';

  tree.remove(10);
  std::cout << "Removed 10 from the tree.\n";
  tree.print();
  std::cout << "Searching for 10 in the tree: "
            << (tree.is_contain(10) ? "Found" : "Not Found") << '\n';
}

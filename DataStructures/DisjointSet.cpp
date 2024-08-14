#include <iostream>
#include <vector>

class DisjointSet {
 public:
  explicit DisjointSet(int n) : parent_(n), rank_(n, 0) {
    make_set();
  }

  int find(int x) {
    if (parent_[x] != x) {
      parent_[x] = find(parent_[x]);
    }
    return parent_[x];
  }

  void union_sets(int x, int y) {
    int x_root = find(x);
    int y_root = find(y);

    if (x_root == y_root) {
      return;
    }

    if (rank_[x_root] < rank_[y_root]) {
      parent_[x_root] = y_root;
    } else if (rank_[x_root] > rank_[y_root]) {
      parent_[y_root] = x_root;
    } else {
      parent_[y_root] = x_root;
      rank_[x_root]++;
    }
  }

  private:
  std::vector<int> parent_;
  std::vector<int> rank_;

  void make_set() {
    for (size_t i = 0; i < parent_.size(); i++) {
      parent_[i] = i;
    }
  }
};

int main() {
  DisjointSet ds(5);

  ds.union_sets(0, 2);

  ds.union_sets(4, 2);
  
  ds.union_sets(1, 3);
  
  if (ds.find(4) == ds.find(0)) {
    std::cout << "Yes\n";
  } else {
    std::cout << "No\n";
  }

  if (ds.find(1) == ds.find(0)) {
    std::cout << "No\n";
  } else {
    std::cout << "No\n";
  }

  // disjoint set will look like this:
  //       0         1
  //      / \        |
  //     2   4       3

}

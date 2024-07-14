#include <iostream>

template <typename T>
class Queue {
 private:
  struct Node {
    T val;
    Node* next;
    Node(const T& val, Node* next = nullptr) : val(val), next(next) {}
  };
  Node* head;
  Node* tail;

 public:
  Queue() : head(nullptr), tail(nullptr) {}
  ~Queue() {
    while (head != nullptr) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }

  void insert(const T& val) {
    Node* node = new Node(val);
    if (tail != nullptr) {
      tail->next = node;
    }
    tail = node;
    if (head == nullptr) {
      head = tail;
    }
  }

  void remove() {
    if (head == nullptr) {
      return;
    }
    Node* deleted_node = head;
    head = head->next;
    delete deleted_node;
    if (head == nullptr) {
      tail = nullptr;
    }
  }

  void print() const {
    Node* current = head;
    while (current != nullptr) {
      std::cout << current->val << " -> ";
      current = current->next;
    }
    std::cout << "nullptr" << '\n';
  }
};

int main() {
  Queue<int> q;

  q.insert(1);
  q.insert(2);
  q.insert(3);
  q.print();

  q.remove();
  q.print();
}

#include <iostream>

template <typename T>
class Stack {
 private:
  struct Node {
    T val;
    Node* next;
    Node(T val, Node* next = nullptr) : val(val), next(next) {}
  };
  Node* head;

 public:
  Stack() : head(nullptr) {}

  ~Stack() {
    while (head != nullptr) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }

  Stack(const Stack& other) : head(nullptr) {
    if (other.head != nullptr) {
      head = new Node(other.head->val);
      Node* current = head;
      Node* other_current = other.head->next;
      while (other_current != nullptr) {
        current->next = new Node(other_current->val);
        current = current->next;
        other_current = other_current->next;
      }
    }
  }

  void push(const T& val) {
    Node* node = new Node(val, head);
    head = node;
  }

  void pop() {
    if (head == nullptr) {
      return;
    }
    Node* new_head = head->next;
    delete head;
    head = new_head;
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
  Stack<int> s;
  s.push(1);
  s.push(2);
  s.print();

  s.pop();
  s.print();
}

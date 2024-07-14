#include <forward_list>
#include <iostream>

template <typename T>
class ForwardList {
 private:
  struct Node {
    T val;
    Node* next;
    Node(T value) : val(value), next(nullptr) {}
  };
  Node* head;

 public:
  ForwardList() : head(nullptr) {}

  ForwardList(std::initializer_list<T> list) : head(nullptr) {
    for (auto it = std::rbegin(list); it != std::rend(list); ++it) {
      insert_after(nullptr, *it);
    }
  }

  ~ForwardList() {
    while (head != nullptr) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }

  void insert_after(Node* ptr, T val) {
    Node* new_node = new Node(val);
    if (ptr == nullptr) {
      new_node->next = head;
      head = new_node;
    } else {
      new_node->next = ptr->next;
      ptr->next = new_node;
    }
  }

  void delete_after(Node* ptr) {
    if (ptr == nullptr || ptr->next == nullptr) {
      return;
    }

    Node* deleted_node = ptr->next;
    ptr->next = ptr->next->next;

    delete deleted_node;
  }

  void printList() const {
    Node* current = head;
    while (current != nullptr) {
      std::cout << current->val << " -> ";
      current = current->next;
    }
    std::cout << "nullptr" << '\n';
  }

  Node* getHead() const { return head; }
};

int main() {
  ForwardList<int> list = {1, 2, 3, 4, 5};
  list.printList();

  list.insert_after(list.getHead(), 10);
  list.printList();

  list.delete_after(list.getHead());
  list.printList();
}

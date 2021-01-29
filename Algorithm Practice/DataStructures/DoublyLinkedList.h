#pragma once

#include <ostream>
#include <vector>

namespace DataStructures {

using std::ostream;
// IDEA: need to decide if should use & or pointer in return types

template <typename T>
struct ListNode {
  ListNode<T>* prev = nullptr;
  ListNode<T>* next = nullptr;
  T data;

  ListNode() : data{} {}
  ListNode(T data) : data{data} {}
  ListNode(const ListNode<T>& node) : data{node.data}, prev{nullptr}, next{nullptr} {}

  ListNode<T>& operator=(const ListNode<T>& node) {
    this->data = node.data;
    return *this;
  }

  bool operator==(const ListNode<T>& l) const {
    return (this->prev == l.prev) && (this->next == l.next);  // shouldn't need to check the value because the nodes identity is it's position in the list
  }

  bool operator!=(const ListNode<T>& l) const {
    return !(*this == l);
  }

  friend ostream& operator<<(ostream& o, const ListNode<T>& l) {
    o << l.data;
    return o;
  }
};

/*
The insert operations track the size of the list and return a pointer to the node added.
When using a ListNode pointer you shouldn't manually change the pointers to the next/prev nodes, because the size would not be updated
*/
template <typename T>
class DoublyLinkedList {
 private:
  int size = 0;

  // Initialises head and tail if they are both null, and returns a pointer to the new node if head and tail are null, otherwise returns null
  ListNode<T>* initialiseFirstElement(const T& data) {
    ListNode<T>* newnode = nullptr;
    if (head == nullptr && tail == nullptr) {
      newnode = new ListNode<T>{data};
      head = newnode;
      tail = newnode;
    }

    return newnode;
  }

  void copyListContent(const DoublyLinkedList<T>& list) {
    this->clearLinkedList();

    this->head = new ListNode<T>{list.head->data};
    this->size = 1;

    ListNode<T>* thiscurr = head;
    ListNode<T>* curr = list.head->next;
    while (curr) {
      thiscurr = insertAfterNode(curr->data, thiscurr);
      curr = curr->next;
      size++;
    }
  }

  void clearLinkedList() {
    ListNode<T>* temp = head;
    ListNode<T>* tempprev;
    while (temp) {
      tempprev = temp;
      temp = temp->next;
      delete tempprev;
    }
  }

 public:
  // IDEA: not a good idea for this, but originally had getters/setters, but this is equivalent in the way I was using it
  ListNode<T>* head = nullptr;
  ListNode<T>* tail = nullptr;

  DoublyLinkedList() {}

  ~DoublyLinkedList() {
    this->clearLinkedList();
  }

  DoublyLinkedList(const DoublyLinkedList<T>& list) {
    copyListContent(list);
  }

  int getSize() {
    return size;
  }

  // need to instansiate head and tail as the same as soon as an element is added
  ListNode<T>* insertBeforeHead(T& data) {
    auto init = initialiseFirstElement(data);
    if (init) return init;

    this->head = this->insertBeforeNode(data, head);
    return this->head;
  }

  ListNode<T>* insertAfterHead(T& data) {
    auto init = initialiseFirstElement(data);
    if (init) return init;

    ListNode<T>* afterHead = this->insertAfterNode(data, head);
    return afterHead;
  }

  ListNode<T>* insertBeforeTail(T& data) {
    auto init = initialiseFirstElement(data);
    if (init) return init;

    ListNode<T>* beforeTail = this->insertBeforeNode(data, tail);
    return beforeTail;
  }

  ListNode<T>* insertAfterTail(T& data) {
    auto init = initialiseFirstElement(data);
    if (init) return init;

    this->tail = this->insertAfterNode(data, tail);
    return this->tail;
  }

  // must be a node in this linked list
  ListNode<T>* insertBeforeNode(T& data, ListNode<T>* node) {
    auto tempprev = node->prev;
    auto newnode = new ListNode<T>{data};

    if (tempprev) {
      head = newnode;  // if node.prev is null then the node was the head, this makes the new node the new head
    }

    node->prev = newnode;
    newnode->next = node;
    newnode->prev = tempprev;

    ++size;

    return newnode;
  }

  // must be a node in this linked list
  ListNode<T>* insertAfterNode(T& data, ListNode<T>* node) {
    auto tempnext = node->next;
    auto newnode = new ListNode<T>{data};

    if (!tempnext) {
      tail = newnode;  // if tempnext is null then the node was the tail, this makes the new node the new tail
    }

    node->next = newnode;
    newnode->prev = node;
    newnode->next = tempnext;

    ++size;

    return newnode;
  }

  // must be a node in this linked list
  void removeNode(ListNode<T>* node) {
    auto tempprev = node->prev;
    auto tempnext = node->next;

    if (tempprev == nullptr) {  // if trying to remove head
      head = node->next;
    } else {
      node->prev->next = tempnext;
    }

    if (tempnext == nullptr) {  // if trying to remove tail
      tail = node->prev;
    } else {
      node->next->prev = tempprev;
    }

    --size;

    delete node;
  }

  DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& list) {
    if (this == &list) return *this;
    copyListContent(list);
    return *this;
  }

  // negative indicies get from the tail end, e.g. a[-1] returns the tail element. And a nullptr is returned if i is larger than the number of elements in the list
  ListNode<T>* operator[](int i) {
    if (i < -size || i >= size) return nullptr;

    ListNode<T>* temp = nullptr;
    if (i < 0) {
      temp = tail;

      int k = -i - 1;
      while (k > 0) {
        temp = temp->prev;
        --k;
      }
    } else {
      temp = head;
      int k = i;
      while (k > 0) {
        temp = temp->next;
        --k;
      }
    }

    return temp;
  }

  friend ostream& operator<<(ostream& o, const DoublyLinkedList<T>& l) {
    if (l.head == nullptr && l.tail == nullptr) {
      o << "{ }";
    } else {
      o << "{ ";
      ListNode<T>* curr = l.head;

      while (curr != l.tail) {
        o << curr->data << ", ";
        curr = curr->next;
      }

      o << l.tail->data << " }";
    }

    return o;
  }
};

}  // namespace DataStructures

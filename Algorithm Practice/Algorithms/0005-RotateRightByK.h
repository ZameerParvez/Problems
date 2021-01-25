#pragma once

#include "../DataStructures/DoublyLinkedList.h"
#include "Algorithm.h"

namespace Algorithms {

// This algorithm rotates a linked list right by k, so that the (size - kth) element becomes the new end of the list
class RotateRightK : public Algorithm {
 private:
  DoublyLinkedList<int> list;
  int kright;

  // assumes singly linked list, so isn't taking advantage of the doubly linked datastructure, or updating the datastructure properly
  // for example the head and tail are not automatically updated, and backwards links are not updated
  ListNode<int>* rotateRight(ListNode<int>* head, int k);

 public:
  int parseInput(istream& input) override;
  int solve(ostream& output) override;
};

}  // namespace Algorithms

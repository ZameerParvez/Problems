#pragma once

#include "../DataStructures/DoublyLinkedList.h"
#include "Algorithm.h"

namespace Algorithms {

using DataStructures::DoublyLinkedList;
using DataStructures::ListNode;

// Adds 2 decimal numbers where the digits are stored as a linked list starting with the least significant digit
class AddTwoNumbers : public Algorithm {
 private:
  static const int BASE = 10;
  DoublyLinkedList<int> l1, l2;

  DoublyLinkedList<int> intStringToLinkedList(string intString);

 public:
  int parseInput(istream& input) override;
  int solve(ostream& output) override;
};

}  // namespace Algorithms

#pragma once

#include "../DataStructures/DoublyLinkedList.h"
#include "Algorithm.h"

// Adds 2 decimal numbers where the digits are stored as a linked list starting with the least significant digit
class AddTwoNumbers : public Algorithm {
 private:
  static const int BASE = 10;
  DoublyLinkedList<int> l1, l2;

 public:
  int parseInput(istream& input) override;
  int solve(ostream& output) override;
};

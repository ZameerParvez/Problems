#include "0001-AddTwoNumbers.h"

using namespace Algorithms;

// returns a doubly linked list of a decimal number, where the least significant digit is at index 0
DoublyLinkedList<int> AddTwoNumbers::intStringToLinkedList(string intString) {
  DoublyLinkedList<int> list;

  for (int i = 0; i < intString.size() ; i++) {
    // reads the char as a value clamped between 0 and 9
    int val = intString[i] - '0';
    val = (intString[i] - '0' < 0) ? 0 : val;
    val = (intString[i] - '0' > 9) ? 9 : val;

    list.insertBeforeHead(val);
  }
 
  return list;
}

int AddTwoNumbers::parseInput(istream& input) {
  LOG(50, "Reading Input for AddTwoNumbers");
  string num1, num2;
  input >> num1 >> num2;

  l1 = intStringToLinkedList(num1);
  l2 = intStringToLinkedList(num2);
  return 0;
}

int AddTwoNumbers::solve(ostream& output) {
  TIMER("Carry addition with linked list");

  DoublyLinkedList<int> result{};

  // result[i] = l1[i] + l2[i] + c[i-1]
  ListNode<int>* currl1 = l1.head;
  ListNode<int>* currl2 = l2.head;
  int carry = 0;

  while(currl1 != nullptr || currl2 != nullptr) {
    int val1 = (currl1) ? currl1->data : 0;
    int val2 = (currl2) ? currl2->data : 0;

    int sum = val1 + val2 + carry;
    int data = sum % BASE;
    carry = sum / BASE;

    result.insertAfterTail(data);

    // if null next will also be null
    currl1 = (currl1) ? currl1->next : nullptr;
    currl2 = (currl2) ? currl2->next : nullptr;
  }

  if (carry > 0) {
    result.insertAfterTail(carry);
  }

  output << "Sum = " << result << std::endl;
  return 1;
}
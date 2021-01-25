#include "0005-RotateRightByK.h"

using std::string;

using namespace Algorithms;

int RotateRightK::parseInput(istream& input) {
  LOG(50, "Rotating linked list right by k");
  
  string line;
  getline(input, line);
  std::stringstream s{line};

  s >> kright;
  int curr;
  while (s >> curr) {
    list.insertAfterTail(curr);
  }

  return 0;
}

int RotateRightK::solve(ostream& output) {
  TIMER("Timer for rotating linked list right by k");
  
  ListNode<int>* actualHead = rotateRight(list.head, kright);
  ListNode<int>* newtail = list.head;
  while (newtail->next) {
    newtail = newtail->next;
  }

  list.head = actualHead;
  list.tail = newtail;

  output << "The original list rotated right by " << kright << " is " << list << std::endl;

  return 0;
}

ListNode<int>* RotateRightK::rotateRight(ListNode<int>* head, int k) {
  if (!head) return head;

  ListNode<int>* current = head;
  ListNode<int>* newhead = nullptr;

  // calculate size
  int size = 1;
  while (current->next) {
    current = current->next;
    ++size;
  }

  if (k % size == 0) return head;  // terminate early if there isn't actually a rotation to be done

  // because there is a rotation to be done, then make the tail loop to the head
  current->next = head;

  int simplifiedR = size - (k % size);  // this would mark the position that would become the new end

  // reset current
  current = head;

  // loop until current is the new tail node
  while (--simplifiedR > 0) {
    current = current->next;
  }

  newhead = current->next;
  current->next = nullptr;

  return newhead;
}
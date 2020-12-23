// initial thoughts
// typed doulby linked list
// node should hold data type value, statically allocated with respect to the node
// next and prev pointers should be available.

// template<typename T>
// class ListNode {
//  private:
//   ListNode<T>* next = nullptr;
//   ListNode<T>* prev = nullptr;
//   T data;
//   std::vector<ListNode<T>*>* deleteList;

//  public:
//   ListNode() : data{}, next{nullptr}, prev{nullptr};  // initialises an empty node with no value for data

//   ListNode(std::vector<ListNode<T>*>* deleteList) : deleteList{deleteList}, data{}, next{nullptr}, prev{nullptr};  // initialises an empty node with no value for data

//   ListNode(T x) : data{x}, next{nullptr}, prev{nullptr};  // initialises a node with no links but some data

//   ListNode(T x, ListNode<T>* next) : data{x}, next{next}, prev{nullptr} { // initialises a node and doubly links it with the next node
//     ListNode<T>* temp = next->prev;

//     while (temp != this) {  // this should iterate through all of the nodes, backwards until either the end is reached or this node is reached, for the case where someone tries to add a node already in the list to the list
//       ListNode<T>* temp2 = temp->prev;
//       removeNode(temp); // this deletes the pointd to node, and then updates temp to the next node to check again, the delete could be delayed if deletes are queued elswhere first
//       temp = temp2;
//     }

//     next->prev = this;
//   }

//   ListNode(ListNode<T>* prev, T x) : data{x}, next{nullptr}, prev{prev} { // initialises a node and doubly links it with the prev node
//     ListNode<T>* temp = prev->next;

//     while (temp != this) {  // this should iterate through all of the nodes until either the end is reached or this node is reached, for the case where someone tries to add a node already in the list to the list
//       ListNode<T>* temp2 = temp->next;
//       removeNode(temp);  // this deletes the pointd to node, and then updates temp to the next node to check again, the delete could be delayed if deletes are queued elswhere first
//       temp = temp2;
//     }

//     prev->next = this;
//   }

//   ListNode(ListNode<T>* prev, T x, ListNode<T>* next) : data{x}, next{next}, prev{prev} { // inserts a new node between prev and next (there aren't any checks for skipping groups of entries yet)
//     // probably not useful here, actually might need to queue the other nodes between to be deleted
//     ListNode<T>* temp = prev->next;
//     /*
//     iterate from prev to next
//     if prev.next == next then no need to continue iterating, just setup the links to the node to insert
//     if prev.next == this, then skip over this and continue checking if this.next == next
//     */
//     while (temp != next) {  // this should iterate through all of the nodes until either the end is reached or this node is reached, for the case where someone tries to add a node already in the list to the list
//       ListNode<T>* temp2 = temp->next;
//       if (temp != this) removeNode(temp);  // should only delete nodes if between prev and next, and not this
//       temp = temp2;
//     }

//     // setting these pointers may not be necessary
//     prev->next = this;
//     next->prev = this;
//   }

//   ~ListNode() { // should handle deleting nodes by updating surrounding noded pointers
//     next->prev = (this->prev) ? this->prev : nullptr;
//     prev->next = (this->next) ? this->next : nullptr;
//   }

//   static bool removeNode(ListNode<T>* l) { // execute delete handles whether l is already in the list
//     if (!l) return false;
//     if (deleteList) {
//       deleteList->emplace_back(l);
//     } else {
//       delete l;
//     }

//     return true;
//   }

//   void clearDeleteList() {
//     for (ListNode<T>* l : *deleteList) {
//       if (!l) delete l;
//     }
//   }

// };

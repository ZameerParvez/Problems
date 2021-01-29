#pragma once

#include <iostream>
#include <ostream>
#include <vector>

// TODO: add copy constructor and assignment operator
// the copy constructor could be implemented by adding new nodes to a new tree in a breadth first way
// adding the nodes in order would make the bst's performance degrade to a linked list

// IDEA: there could be a way to tidy some of the code, specifically some of the nested if statements, and similar search loops
// IDEA: could also try to improve the way the tree is output, maybe have another function to append to a vector in order

// this will be a binary tree stored as a arrays, not an nodes
// will have Search(D,k), Insert(D,x), Delete(D,x)
// nodes will have only references to their children and some data
namespace DataStructures {

template <typename T>
struct BinaryTreeNode {
  T data;
  BinaryTreeNode* left = nullptr;
  BinaryTreeNode* right = nullptr;
  BinaryTreeNode(T d) : data{d} {}

  friend std::ostream& operator<<(std::ostream& o, const BinaryTreeNode<T>* node) {
    if (node == nullptr) return o;
    o << node->left;
    o << node->data << ", ";
    o << node->right;
    return o;
  }
};

// does not allow duplicate entries
template <typename T>
class SimpleBST {
 private:
  BinaryTreeNode<T>* root = nullptr;

  bool DeleteSubTree(BinaryTreeNode<T>* node) {
    if (node == nullptr) return false;
    // do deletions in postorder
    DeleteSubTree(node->left);
    DeleteSubTree(node->right);
    delete node;
    return true;
  }

 public:
  SimpleBST(const std::vector<T>& in) {
    for (T t : in) {
      Insert(t);
    }
  }

  ~SimpleBST() {
    DeleteSubTree(root);
  }

  bool Delete(const T& t) {
    // make sure node to delete is in the tree
    // then move nodes around based on a few cases, to make sure there aren't any gaps in the tree
    // there are 3 cases to deal with
    // node with 0 childs
    // node with 1 childs
    // node with 2 childs
    BinaryTreeNode<T>* curr = root;
    BinaryTreeNode<T>* parent = nullptr;

    // should get the node that is equal to t, and it's parent
    while (curr != nullptr && t != curr->data) {
      parent = curr;
      if (t < curr->data) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }

    // node to delete wasn't in list
    if (curr == nullptr) {
      return false;
    }

    if (curr->left == nullptr && curr->right == nullptr) {
      // 0 child nodes
      if (parent != nullptr) {
        if (curr->data < parent->data) {
          // delete left child
          parent->left = nullptr;
        } else {
          // delete right child
          parent->right = nullptr;
        }
      } else {
        root = nullptr;
      }

      delete curr;
      return true;
    } else if (curr->left != nullptr && curr->right != nullptr) {
      // 2 child nodes
      // get the next smallest node in the tree, and its parent
      BinaryTreeNode<T>* successor = curr->right;
      BinaryTreeNode<T>* successorParent = curr;
      while (successor->left != nullptr) {
        successorParent = successor;
        successor = successor->left;
      }

      // if the node to be deleted is the root, then it doesn't have a parent, but the root pointer needs updating
      // set curr's parent to point to the sucessor, instead of curr
      if (parent != nullptr) {
        if (curr->data < parent->data) {
          parent->left = successor;
        } else {
          parent->right = successor;
        }
      } else {
        root = successor;
      }

      // different logic for swapping curr and successor, if successor is curr's direct child
      if (successor == curr->right) {
        // successor's parent would be curr, so the swap should be simpler
        BinaryTreeNode<T>* tempPoint = successor->right;
        successor->left = curr->left;
        successor->right = curr;

        curr->left = nullptr;
        curr->right = tempPoint;

        // remove curr after it has been swapped
        successor->right = curr->right;
      } else {
        BinaryTreeNode<T>* tempPoint = successor->right;
        successor->right = curr->right;
        successor->left = curr->left;

        successorParent->left = curr;
        curr->left = nullptr;  // because successor->left must be null if it is the immediate successor
        curr->right = tempPoint;

        // remove curr after it has been swapped
        successorParent->left = curr->right;
      }

      delete curr;
      return true;
    } else {
      // 1 child nodes
      // case where the root node is being deleted, and it only has one child
      if (parent != nullptr) {
        if (curr->data < parent->data) {
          if (curr->left != nullptr) {
            parent->left = curr->left;
          } else {
            parent->left = curr->right;
          }
        } else {
          if (curr->left != nullptr) {
            parent->right = curr->left;
          } else {
            parent->right = curr->right;
          }
        }
      } else {
        root = (curr->left != nullptr) ? curr->left : curr->right;
      }

      delete curr;
      return true;
    }

    return false;
  }

  const BinaryTreeNode<T>* Insert(const T& t) {
    BinaryTreeNode<T>* curr = root;
    BinaryTreeNode<T>* parent = nullptr;

    if (curr == nullptr) {
      // there were no nodes in the tree
      root = new BinaryTreeNode<T>{t};
      return root;
    }

    while (curr != nullptr) {
      parent = curr;
      if (t == curr->data) {
        return nullptr;
      } else if (t < curr->data) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }

    // put new node to the left or right of the child
    if (t < parent->data) {
      parent->left = new BinaryTreeNode<T>{t};
      curr = parent->left;
    } else {
      parent->right = new BinaryTreeNode<T>{t};
      curr = parent->right;
    }

    return curr;
  }

  const BinaryTreeNode<T>* Search(const T& t) {
    BinaryTreeNode<T>* curr = root;

    while (curr != nullptr) {
      if (t == curr->data) {
        return curr;
      } else if (t < curr->data) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }

    // not found
    return nullptr;
  }

  friend std::ostream& operator<<(std::ostream& o, const SimpleBST<T>& bst) {
    o << "{ ";
    if (bst.root != nullptr) {
      o << bst.root;
    }
    o << " }";
    return o;
  }
};

}  // namespace DataStructures

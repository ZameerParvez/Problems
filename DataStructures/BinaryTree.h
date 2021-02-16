#pragma once

#include <sstream>
#include <string>

#include "../Util/OutputHelp.h"

namespace DataStructures {

using Util::operator<<;

template <typename T>
struct BinaryTreeNode {
  T data;
  BinaryTreeNode* left = nullptr;
  BinaryTreeNode* right = nullptr;
  BinaryTreeNode(T d) : data{d} {}

  friend std::ostream& operator<<(std::ostream& o, const BinaryTreeNode<T>* node) {
    o << node->data;
    return o;
  }
};

// this does not update the pointer of the parent node
template <typename T>
bool DeleteSubTree(BinaryTreeNode<T>* node) {
  if (node == nullptr) return false;
  // do deletions in postorder
  DeleteSubTree(node->left);
  DeleteSubTree(node->right);
  delete node;
  return true;
}

template <typename T>
bool DeleteLeftSubTree(BinaryTreeNode<T>* node) {
  if (node == nullptr) return false;
  if (DeleteSubTree(node->left)) {
    node->left = nullptr;
    return true;
  } else {
    return false;
  }
}

template <typename T>
bool DeleteRightSubTree(BinaryTreeNode<T>* node) {
  if (node == nullptr) return false;
  if (DeleteSubTree(node->right)) {
    node->right = nullptr;
    return true;
  } else {
    return false;
  }
}

template <typename T>
bool DeleteNodeChildren(BinaryTreeNode<T>* node) {
  bool a = DeleteLeftSubTree(node);
  bool b = DeleteRightSubTree(node);

  return a && b;
}

enum class BinaryTreeTraverseOrder {
  PREORDER,
  INORDER,
  POSTORDER
};

template <typename T>
void btOut(BinaryTreeNode<T>* node, std::vector<BinaryTreeNode<T>*>& v, const BinaryTreeTraverseOrder& t) {
  if (node == nullptr) return;
  switch (t) {
    case BinaryTreeTraverseOrder::PREORDER:
      v.push_back(node);
      btOut(node->left, v, BinaryTreeTraverseOrder::PREORDER);
      btOut(node->right, v, BinaryTreeTraverseOrder::PREORDER);
      return;
    case BinaryTreeTraverseOrder::INORDER:
      btOut(node->left, v, BinaryTreeTraverseOrder::INORDER);
      v.push_back(node);
      btOut(node->right, v, BinaryTreeTraverseOrder::INORDER);
      return;
    case BinaryTreeTraverseOrder::POSTORDER:
      btOut(node->left, v, BinaryTreeTraverseOrder::POSTORDER);
      btOut(node->right, v, BinaryTreeTraverseOrder::POSTORDER);
      v.push_back(node);
      return;
    default:
      btOut(node->left, v, BinaryTreeTraverseOrder::INORDER);
      v.push_back(node);
      btOut(node->right, v, BinaryTreeTraverseOrder::INORDER);
      return;
  }
}

template <typename T>
std::string binaryTreeToString(BinaryTreeNode<T>* node, BinaryTreeTraverseOrder t = BinaryTreeTraverseOrder::INORDER) {
  std::vector<BinaryTreeNode<T>*> nodes;
  btOut(node, nodes, t);

  std::ostringstream os;
  os << nodes;
  return os.str();
}

}  // namespace DataStructures
#pragma once

#include <unordered_map>
#include <vector>

#include "../DataStructures/BinaryTree.h"
#include "Algorithm.h"

namespace Algorithms {

// This algorithm builds a binary tree from an inorder and preorder list of nodes in the tree
class BuildBinaryTreeIP : public Algorithm {
 private:
  std::vector<int> preorder;
  std::vector<int> inorder;

  static DataStructures::BinaryTreeNode<int>* buildSubTree(
      std::unordered_map<int, int>& numToInorderIndex,
      const std::vector<int>& preorder,
      const std::vector<int>& inorder,
      int rootIndexPreorder,
      int startIndexInOrder,
      int endIndexInOrder);

 public:
  static DataStructures::BinaryTreeNode<int>* buildTree(const std::vector<int>& preorder, const std::vector<int>& inorder);

  int parseInput(istream& input) override;
  int solve(ostream& output) override;
};

}  // namespace Algorithms

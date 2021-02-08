#include "0008-BuildBinaryTreeWithInorderAndPreorder.h"

#include <string>
#include <unordered_map>
#include <vector>

#include "../Util/OutputHelp.h"

using DataStructures::BinaryTreeNode;
using std::string;
using std::unordered_map;
using std::vector;
using Util::operator<<;

using namespace Algorithms;

int BuildBinaryTreeIP::parseInput(istream& input) {
  LOG(50, "Inputing preorder and inorder list of nodes");
  string line;

  getline(input, line);
  std::istringstream s{line};
  int curr;

  while (s >> curr) {
    preorder.emplace_back(curr);
  }

  getline(input, line);
  s = std::istringstream{line};

  while (s >> curr) {
    inorder.emplace_back(curr);
  }

  if (inorder.size() != preorder.size()) return -1;

  return 0;
}

BinaryTreeNode<int>* BuildBinaryTreeIP::buildSubTree(
    unordered_map<int, int>& numToInorderIndex,
    const vector<int>& preorder,
    const vector<int>& inorder,
    int rootIndexPreorder,
    int startIndexInOrder,
    int endIndexInOrder) {
  if (rootIndexPreorder > preorder.size()) return nullptr;

  int root = preorder[rootIndexPreorder];
  BinaryTreeNode<int>* rootNode = new BinaryTreeNode<int>(root);

  if (startIndexInOrder == endIndexInOrder) return rootNode;

  // use hashmap here to gain constant time lookup for the index of the root of the current subtree, in the inorder list
  int rootIndexInOrder = numToInorderIndex[root];

  // build left sub tree
  int sizeOfLeftSubTree = rootIndexInOrder - startIndexInOrder;
  if (sizeOfLeftSubTree > 0) {
    rootNode->left = buildSubTree(numToInorderIndex, preorder, inorder, rootIndexPreorder + 1, startIndexInOrder, rootIndexInOrder - 1);
  }

  // build right sub tree
  int sizeOfRightSubTree = endIndexInOrder - rootIndexInOrder;
  if (sizeOfRightSubTree > 0) {
    rootNode->right = buildSubTree(numToInorderIndex, preorder, inorder, rootIndexPreorder + sizeOfLeftSubTree + 1, rootIndexInOrder + 1, endIndexInOrder);
  }

  return rootNode;
}

BinaryTreeNode<int>* BuildBinaryTreeIP::buildTree(const vector<int>& preorder, const vector<int>& inorder) {
  TIMER("The binary tree was built in");
  if (preorder.size() == 0 || inorder.size() == 0) return nullptr;

  unordered_map<int, int> numToInorderIndex;
  for (int i = 0; i < inorder.size(); i++) {
    numToInorderIndex[inorder[i]] = i;
  }

  return buildSubTree(numToInorderIndex, preorder, inorder, 0, 0, preorder.size() - 1);
}

int BuildBinaryTreeIP::solve(ostream& output) {
  auto tree = buildTree(this->preorder, this->inorder);

  output
      << "The following is the constructed binary tree in preorder, inorder and postorder forms: \n"
      << "Preorder : " << DataStructures::binaryTreeToString(tree, DataStructures::BinaryTreeTraverseOrder::PREORDER) << "\n"
      << "Inorder : " << DataStructures::binaryTreeToString(tree, DataStructures::BinaryTreeTraverseOrder::INORDER) << "\n"
      << "Postorder : " << DataStructures::binaryTreeToString(tree, DataStructures::BinaryTreeTraverseOrder::POSTORDER) << "\n"
      << std::endl;

  DataStructures::DeleteSubTree(tree);

  return 0;
}

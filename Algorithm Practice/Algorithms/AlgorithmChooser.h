#pragma once

#include "AlgorithmCollection.h"

struct AlgorithmWrapper {
  Algorithm* algorithm;
  
  AlgorithmWrapper(Algorithm* a = nullptr) : algorithm{a} {}
  ~AlgorithmWrapper() {
    delete algorithm;
  }
};

// This function uses the integer given to return a child instance of the algorithm
AlgorithmWrapper choose(int i) {
  AlgorithmWrapper a{};

  switch (i) {
    case 0:
      a.algorithm = new Sum{};
      break;
    case 1:
      a.algorithm = new AddTwoNumbers{};
      break;
    default:
      a.algorithm = new Sum{};
      break;
  }

  return a;
}

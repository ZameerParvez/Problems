#pragma once

#include "AlgorithmCollection.h"

namespace Algorithms {

// This function uses the integer given to return a child instance of the algorithm
AlgorithmWrapper choose(int i) {
  switch (i) {
    case 0:
      return AlgorithmWrapper{new Test{}};
    case 1:
      return AlgorithmWrapper{new AddTwoNumbers{}};
    case 2:
      return AlgorithmWrapper{new LCS1Char{}};
    case 3:
      return AlgorithmWrapper{new CoinChange{}};
    case 4:
      return AlgorithmWrapper{new SmallestSubstrWithSameOrder{}};
    default:
      return AlgorithmWrapper{new Test{}};
  }
}

}  // namespace Algorithms

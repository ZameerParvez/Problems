#pragma once

#include "AlgorithmCollection.h"

namespace Algorithms {

// IDEA: automate choosing algorithms, by doing something like keeping a large vector, where the algorithms can be retrieved by their index

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
    case 5:
      return AlgorithmWrapper{new RotateRightK{}};
    case 6:
      return AlgorithmWrapper{new DaysUntilHotter{}};
    default:
      return AlgorithmWrapper{new Test{}};
  }
}

}  // namespace Algorithms

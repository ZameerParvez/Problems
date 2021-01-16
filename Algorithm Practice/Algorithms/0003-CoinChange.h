#pragma once

#include "Algorithm.h"

namespace Algorithms {

// Computes the number of different ways to make a change for an amount n, given an infinite supply of coins from the currencies denominations
// e.g. n=5 , denominations=[1,3,5], there are only 3 ways to make 5 from these denominations: {1,1,1,1,1},{1,1,3},{5}
class CoinChange : public Algorithm {
 private:
  vector<int> denominations{};
  int target = 0;

 public:
  int parseInput(istream& input) override;
  int solve(ostream& output) override;
};

}  // namespace Algorithms

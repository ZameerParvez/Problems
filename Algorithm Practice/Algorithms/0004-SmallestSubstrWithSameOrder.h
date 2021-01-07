#pragma once

#include "Algorithm.h"

// Finds the smallest substring that maintains the order of the string, where the order is the frequency of the most frequent element
class SmallestSubstrWithSameOrder : public Algorithm {
 private:
  string inputstring;

 public:
  int parseInput(istream& input) override;
  int solve(ostream& output) override;
};

#pragma once

#include "Algorithm.h"

// finds the size of the longest common substring without repeating characters
class LCS1Char : public Algorithm {
 private:
  string s{};

 public:
  int parseInput(istream& input) override;
  int solve(ostream& output) override;
};

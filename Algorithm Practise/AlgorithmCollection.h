#pragma once

#include "Algorithm.h"

class Sum : public Algorithm {
 private:
  vector<int> numbers;
  int sum = 0;

 public:
  int parseInput(istream& input) override;
  int solve(ostream& output) override;
};


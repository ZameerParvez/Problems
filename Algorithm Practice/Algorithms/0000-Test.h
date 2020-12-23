#pragma once

#include "Algorithm.h"

// This is  a simple test to make sure the framework builds and runs properly
class Sum : public Algorithm {
 private:
  vector<int> numbers;
  int sum = 0;

 public:
  int parseInput(istream& input) override;
  int solve(ostream& output) override;
};


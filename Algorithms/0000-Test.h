#pragma once

#include "Algorithm.h"

namespace Algorithms {

// This is  a simple test to make sure the framework builds and runs properly
class Test : public Algorithm {
 private:
 public:
  int parseInput(istream& input) override;
  int solve(ostream& output) override;
};

}  // namespace Algorithms

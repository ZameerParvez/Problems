#pragma once

#include <vector>

#include "Algorithm.h"

namespace Algorithms {

// This algorithm returns an array giving the number of days until the next hottest day, where the day is indicated by the index of the input list of temperatures
class DaysUntilHotter : public Algorithm {
 private:
  std::vector<int> tempsOnDays;

 public:
  int parseInput(istream& input) override;
  int solve(ostream& output) override;
};

}  // namespace Algorithms

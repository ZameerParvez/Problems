#pragma once

#include <tuple>
#include <vector>

#include "Algorithm.h"

namespace Algorithms {

// This is algorithm merges the intervals given in the form of {{small, big}, {small, big}}, from 2 lists of intervals
class MergeIntervals : public Algorithm {
 private:
  std::vector<std::pair<int, int>> intervalsA;
  std::vector<std::pair<int, int>> intervalsB;

 public:
  static std::vector<std::pair<int, int>> mergeIntervals(const std::vector<std::pair<int, int>>& inA, const std::vector<std::pair<int, int>>& inB);

  int parseInput(istream& input) override;
  int solve(ostream& output) override;
};

}  // namespace Algorithms

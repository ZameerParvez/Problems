#include "0007-MergeIntervals.h"

#include <algorithm>
#include <vector>

#include "../Util/OutputHelp.h"

using std::pair;
using std::string;
using std::vector;
using Util::operator<<;

using namespace Algorithms;

vector<pair<int, int>> makeIntervals(vector<int>& v) {
  // the input didn't have pairs of ints for all of the intervals
  if (v.size() % 2 == 1) {
    return {};
  }

  vector<pair<int, int>> intervals;
  for (int i = 0; i < v.size() - 1; i += 2) {
    intervals.emplace_back(pair<int, int>{v[i], v[i + 1]});
  }

  return intervals;
}

// this will always assume that the interval is from small to large number
int MergeIntervals::parseInput(istream& input) {
  LOG(50, "This should be logging the input stage of the MergeIntervals algorithm");
  string line;
  int curr;

  getline(input, line);
  std::istringstream s{line};

  // IDEA: this isn't an efficient method of inputting the intervals, it also isn't the tidiest in the input file, so it could be improved a lot
  vector<int> plainListOfIntsA;
  while (s >> curr) {
    plainListOfIntsA.emplace_back(curr);
  }

  getline(input, line);
  s = std::istringstream{line};

  vector<int> plainListOfIntsB;
  while (s >> curr) {
    plainListOfIntsB.emplace_back(curr);
  }

  intervalsA = std::move(makeIntervals(plainListOfIntsA));
  intervalsB = std::move(makeIntervals(plainListOfIntsB));

  if (intervalsA.size() == 0 || intervalsB.size() == 0) {
    return -1;
  }

  return 0;
}

vector<pair<int, int>> MergeIntervals::mergeIntervals(const vector<pair<int, int>>& inA, const vector<pair<int, int>>& inB) {
  vector<pair<int, int>> mergedIntervals{};
  int ai = 0;
  int bi = 0;
  int min = 0;
  int max = 0;

  while (ai < inA.size() && bi < inB.size()) {
    // sets min and max to the interval with the smalles start out of the 2 inputs
    if (inA[ai].first < inB[bi].first) {
      min = inA[ai].first;
      max = inA[ai].second;
      ai++;
    } else {
      min = inB[bi].first;
      max = inB[bi].second;
      bi++;
    }

    // merges intervals in A
    while (ai < inA.size() && max >= inA[ai].first) {
      max = std::max(inA[ai].second, max);
      ai++;
    }
    // merges intervals in B
    while (bi < inB.size() && max >= inB[bi].first) {
      max = std::max(inB[bi].second, max);
      bi++;
    }
    // advances the pointer in A to skip merging intervals if it is already known to be in the interval 
    while (ai < inA.size() && max >= inA[ai].first) {
      ai++;
    }

    mergedIntervals.emplace_back(std::move(pair<int, int>{min, max}));
  }

  // add the remaining intervals to the list
  while (ai < inA.size()) {
    mergedIntervals.emplace_back(inA[ai++]);
  }

  while (bi < inB.size()) {
    mergedIntervals.emplace_back(inB[bi++]);
  }

  return mergedIntervals;
}

int comp(const pair<int, int>& a, const pair<int, int>& b) {
  return a.first < b.first;
}

int MergeIntervals::solve(ostream& output) {
  TIMER("This should be the how long it takes to merge the 2 interval lists and merge intervals so that there are no overlaps");

  std::sort(intervalsA.begin(), intervalsA.end(), comp);
  std::sort(intervalsB.begin(), intervalsB.end(), comp);

  // IDEA: this would be a lot simpler if I merged the lists first, and it would be no different, but sorting the merged list would take a bit longers
  // IDEA: could implement an efficient data structure that would manage merging of intervals when they are inserted, so querying for intervals would be quick, and would allow data to be streamed in
  auto result = mergeIntervals(intervalsA, intervalsB);

  output << "The intervals after being merged are " << result << std::endl;

  return 0;
}

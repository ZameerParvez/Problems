#include "0002-LongestCommonSubstr1Char.h"

using namespace Algorithms;

int LCS1Char::parseInput(istream& input) {
  LOG("Reading Input for LongestCommonSubstr1Char", 50);
  input >> s;
  return 0;
}

int LCS1Char::solve(ostream& output) {
  TIMER("Finding the longest common substring without repeating characters");

  int left = 0, right = 0;
  int maxSubIdx[2]{};
  int charCount[128]{}; // this size to accomodate all valid chars, although (int)char could return somthing different in another compiler
  
  while (right < s.size()) {
      int charAtRight = (int)s[right];
      charCount[charAtRight] += 1;
      right += 1;
      
      while (charCount[charAtRight] > 1 && left <= right) { // if we have a repeat char then we should start to increment left until we don't
          int charAtLeft = (int)s[left];
          charCount[charAtLeft] -= 1;
          left += 1;
      }
      
      if (right - left > maxSubIdx[1] - maxSubIdx[0]) {
          maxSubIdx[0] = left;
          maxSubIdx[1] = right;
      }
  }
  
  int size = maxSubIdx[1] - maxSubIdx[0];
  string maxsubstr = s.substr(maxSubIdx[0], size);

  output << "Maximum Substring is: " << maxsubstr << " : size: " << size << std::endl;
  return 1;
}
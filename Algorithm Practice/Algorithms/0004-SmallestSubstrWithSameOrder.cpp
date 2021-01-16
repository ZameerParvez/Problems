#include "0004-SmallestSubstrWithSameOrder.h"

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace Algorithms;

int SmallestSubstrWithSameOrder::parseInput(istream& input) {
  LOG("Reading input for SmallestSubstrWithSameOrder", 50);

  getline(input, inputstring);

  return 0;
}

int SmallestSubstrWithSameOrder::solve(ostream& output) {
  TIMER("The time it took to find the smallest substring that maintains the size of the original size was: ");

  int maxorder = 0;
  std::unordered_map<char, int[3]> numindicies{};
  for (int i = 0; i < inputstring.size(); i++) {
    char num = inputstring[i];
    if (numindicies.find(num) == numindicies.end()) {
      numindicies[num][0] = 1;
      numindicies[num][1] = i;
      numindicies[num][2] = i;
    } else {
      numindicies[num][0] += 1;
      numindicies[num][2] = i;
      if (numindicies[num][0] > maxorder) {
        maxorder = numindicies[num][0];
      }
    }
  }

  int smallestsubstrindicies[2] = {0, inputstring.size()};
  for (auto i = numindicies.begin(); i != numindicies.end(); i++) {
    if (i->second[0] == maxorder) {
      if ((i->second[2] - i->second[1]) < (smallestsubstrindicies[1] - smallestsubstrindicies[0])) {
        smallestsubstrindicies[0] = i->second[1];
        smallestsubstrindicies[1] = i->second[2];
      }
    }
  }

  auto first = inputstring.begin() + smallestsubstrindicies[0];
  auto last = inputstring.begin() + smallestsubstrindicies[1];
  string smallestSubstr{first, last + 1};

  output << "The smallest substring that maitains the order of " << inputstring << " is : " << smallestSubstr << std::endl;

  return 0;
}

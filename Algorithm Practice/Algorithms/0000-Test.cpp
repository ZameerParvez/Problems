#include <iostream>
#include <vector>
#include <sstream>

#include "0000-Test.h"

using namespace Algorithms;

int Test::parseInput(istream& input) {
  LOG("This should be logging the input stage of the test algorithm", 50);
  string line;
  getline(input,line);
  std::stringstream s{line};
  
  vector<string> commaseperated;
  while (s.good()) {
    string substr;
    getline(s, substr, ',');
    commaseperated.push_back(substr);
  }

  return 0;
}

int Test::solve(ostream& output) {
  TIMER("This should be the how long the algorithm being tested should take");
  
  output << "THIS IS THE TEST ALGORITHM,  WHICH COULD MEAN THAT THE ALGORITHM ID ENTERED WAS WRONG" << std::endl;

  return 0;
}
#include "0000-Test.h"

#include <vector>

#include "../Util/OutputHelp.h"

using std::string;
using std::vector;
using Util::operator<<;

using namespace Algorithms;

int Test::parseInput(istream& input) {
  LOG(50, "This should be logging the input stage of the test algorithm");
  string line;
  getline(input, line);
  std::istringstream s{line};

  // read all inputs from the same line, where arrays are space sperarated integers, and different parameters are seperated by bars
  vector<string> barseperated;
  while (s.good()) {
    string substr;
    getline(s, substr, '|');
    barseperated.emplace_back(std::move(substr));
  }

  vector<int> testinput;

  s = std::istringstream{barseperated[0]};
  int curr = 0;
  while (s >> curr) {
    testinput.emplace_back(curr);
  }
  

  return 0;
}

int Test::solve(ostream& output) {
  TIMER("This should be the how long the algorithm being tested should take");
  std::vector<int> a{1, 2, 3, 5, 5, 6};
  std::cout << a << std::endl;

  output << "THIS IS THE TEST ALGORITHM,  WHICH COULD MEAN THAT THE ALGORITHM ID ENTERED WAS WRONG" << std::endl;

  return 0;
}

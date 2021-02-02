#include <vector>

#include "../Util/OutputHelp.h"
#include "0000-Test.h"

using std::vector;
using std::string;
using Util::operator<<;

using namespace Algorithms;

int Test::parseInput(istream& input) {
  LOG(50, "This should be logging the input stage of the test algorithm");
  string line;
  getline(input,line);
  std::istringstream s{line};
  
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
  std::vector<int> a{1,2,3,5,5,6};
  std::cout << a << std::endl;

  output << "THIS IS THE TEST ALGORITHM,  WHICH COULD MEAN THAT THE ALGORITHM ID ENTERED WAS WRONG" << std::endl;

  return 0;
}

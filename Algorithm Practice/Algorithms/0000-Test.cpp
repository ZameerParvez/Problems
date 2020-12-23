#include<iostream>
#include<vector>
#include<sstream>

#include "0000-Test.h"

int Sum::parseInput(istream& input) {
  LOG("This should be logging the input stage of the summing algorithm", 50);
  string line;
  getline(input,line);
  std::stringstream s{line};
  
  vector<string> commaseperated;
  while (s.good()) {
    string substr;
    getline(s, substr, ',');
    commaseperated.push_back(substr);
  }
  for (auto i : commaseperated) {
    numbers.push_back(std::atoi(i.c_str()));
  }

  return 0;
}

int Sum::solve(ostream& output) {
  TIMER("This should be a simple test of timing summing some numbers");
  for (int i : numbers) {
    sum += i;
  }

  output << "Solution: " << sum << std::endl;
  output << "THIS IS THE TEST ALGORITHM,  WHICH COULD MEAN THAT THE ALGORITHM ID ENTERED WAS WRONG" << std::endl;

  return 0;
}
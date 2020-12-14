#include<iostream>
#include<vector>
#include<sstream>
#include<thread>

#include "AlgorithmCollection.h"

int Sum::parseInput(istream& input) {
  Logger::log("This should be logging the input stage of the summing algorithm", 50);
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
  Timer t{"This should be a simple test of timing summing some numbers"};
  for (int i : numbers) {
    sum += i;
  }

  output << "Solution: " << sum << std::endl;

  return 0;
}
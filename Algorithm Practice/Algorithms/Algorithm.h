#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::istream;
using std::ostream;
using std::string;
using std::vector;

#include "../Util/Timer.h"

class Algorithm {
 public:
  virtual ~Algorithm(){}

  // whether the input and output should come/go to terminal/file should be determined by the main caller
  void run(istream& in, ostream& out) {
    this->parseInput(in);
    this->solve(out);
  }

  virtual int parseInput(istream& input) = 0;  // this should parse the input from the stream into some private member varibles
  virtual int solve(ostream& output) = 0;      // osteam so output could go to terminal or text file
};

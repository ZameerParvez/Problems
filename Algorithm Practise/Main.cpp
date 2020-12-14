#include "AlgorithmCollection.h"

int main(int argc, char const *argv[]) {
  Sum test{};
  test.run(std::cin,std::cout);
  Logger& l = Logger::getLogger();
  std::cout << l << std::endl;
  return 0;
}

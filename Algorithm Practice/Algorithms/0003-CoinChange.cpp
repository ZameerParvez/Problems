#include "0003-CoinChange.h"

#include <ostream>
#include <sstream>
#include <vector>

#include "../DataStructures/ArrayList.h"

int CoinChange::parseInput(istream& input) {
  LOG("Reading inputs for the CoinChange Problem", 50);

  string line;
  getline(input, line);
  std::stringstream s{line};

  s >> target;
  int denom;
  while (s >> denom) {
    denominations.push_back(denom);
  }

  return 0;
}

// this assumes that the denominations are sorted in ascending order and are unique in the input
int CoinChange::solve(ostream& output) {
  TIMER("Calculating total number of ways to make a target amount of money with some coin denominations");

  // assumes sorted denominations
  if (target < denominations[0]) {  // the target is smaller than the given denominations so can't be made from them quick exit if given a small target
    return 0;
  }

  // IDEA: Could be able to use less memory by only storing and calculating results in denom[x]-denom[0] sized array, this would involve looping in a window of denom[x]-denom[0], in the inner while loop, until the target is reached
  int memsize = target + 1; // memory to store solutions to sub problems
  int* mem = new int[memsize];
  
  // making sure memory is zeroed
  int i = 0;
  for (int i = 0; i < memsize; i++) {
    mem[i] = 0;
  }

  int smallestDenom = denominations[0];
  mem[0] = 1; // only 1 way to make 0

  // This uses the relation f(n,d[0..x])=f(n,d[0..x-1])+f(n-d[x],d[0..x])
  // It first calculates solutions for d(n,d[0])=d(n-d[0],d[0]) because these solutions to larger problems depend on these, and it is simple to calculate for the smallest denomination
  // Then for d[0..1], f(n,d[0..1])=f(n,d[0])+f(n-d[1],d[0..1]), f(n,d[0]) has already been calculated
  // To calculate f(n-d[1],d[0..1]), start with the smallest possible n, which is n=d[1], where f(n,d[0..1])=f(n,d[0])+f(n-d[1],d[0..1])=f(n,d[0])+1
  // So all problems have a solution involving f(n,d[0]), which is already solved, and f(n-d[1],d[0..1]), which iteratively solved from the smallest valid value of n
  // This is done for all the denominations
  for (int d : denominations) {
    int subT = d;
    while (subT <= target) {
      mem[subT] += mem[subT-d];
      subT++;
    }
  }

  int solution = mem[target];

  output << "Total number of ways to make " << target << " is " << solution << std::endl;
  
  delete[] mem;
  return 0;
}
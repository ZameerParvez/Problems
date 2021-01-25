#include "0006-DaysUntilHotter.h"

#include <stack>

#include "../DataStructures/ArrayList.h"

using std::stack;
using std::string;
using std::vector;

using namespace Algorithms;

int DaysUntilHotter::parseInput(istream& input) {
  LOG(50, "Inputting list of temps");
  string line;
  getline(input, line);
  std::istringstream s{line};

  int curr;
  while (s >> curr) {
    tempsOnDays.emplace_back(curr);
  }
  
  return 0;
}

int DaysUntilHotter::solve(ostream& output) {
  TIMER("Calculating number of days until the next hottest day");

  vector<int> daysUntilHotter(tempsOnDays.size());

  // this stack will store the indices of temperatures seen so far that are greater than the current temperature
  stack<int> st;

  // iterate over the temperatures in reverse order
  for (int i = tempsOnDays.size() - 1; i >= 0; --i) {
    // pop the stack until it only has indices to temperatures greater than the current temp, or until it's empty
    while (!st.empty() && tempsOnDays[i] >= tempsOnDays[st.top()]) st.pop();
    // if the stack is empty then there are no days hotter than the current day, otherwise the number of days until the next hotter day are the difference between the top of the stack and the current day index
    daysUntilHotter[i] = st.empty() ? 0 : st.top() - i;
    st.push(i);
  }
  
  output << "The number of days until the next hotter day, for the given days are " <<  daysUntilHotter << std::endl;

  return 0;
}

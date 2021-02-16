#pragma once

#include <string>
#include <sstream>
#include <stdexcept>

namespace Util {

using std::string;
using std::ostringstream;

// IDEA: compute these at compile time, so it fails early if the format string is malformed, or parameters are missing, I don't think this method could be used for that though

// this is the base case, where there are no parameters to insert into the format string
static void escapestrng(ostringstream& os, const string &formatString, size_t& prevPos, size_t& currPos) {
  if (currPos == string::npos) {
    os << formatString.substr(prevPos, formatString.size() - prevPos);
    return;
  } else if (currPos == prevPos) {
    // then the char at the currFoundPos, was a %, which in this case was the char at 0
    prevPos = currPos + 1;
    currPos = formatString.find('%', prevPos);
    if (prevPos == currPos) {
      // it's a double
      prevPos = currPos + 1;
      currPos = formatString.find('%', prevPos);
      os << '%';
    } else {
      // error, the % was not escaped, and there are no arguments
      ostringstream  errrmessage;
      errrmessage << "The format string contains MORE unescaped % symbols, than arguments, at position " << prevPos << std::endl;
      throw std::invalid_argument(errrmessage.str());
    }
  } else {
    // the first char was not a %
    os << formatString.substr(prevPos, currPos - prevPos);
    prevPos = currPos;
  }

  escapestrng(os, formatString, prevPos, currPos);
}

template<typename T>
extern void fmtstrng(ostringstream& os, const string &formatString, size_t& prevPos, size_t& currPos, const T& t) {
  if (currPos == string::npos) {
    // error, because there is no marker for the parameter being added
    throw std::invalid_argument("The format string contains LESS unescaped % symbols, than arguments");
  } else if (currPos == prevPos) {
    // then the char at the currFoundPos, was a %
    prevPos = currPos + 1;
    currPos = formatString.find('%', prevPos);
    if (prevPos == currPos) {
      // it's a double
      prevPos = currPos + 1;
      currPos = formatString.find('%', prevPos);
      os << '%';
    } else {
      // output t
      os << t;
      escapestrng(os, formatString, prevPos, currPos);
      return;
    }
  } else {
    // the first char was not a %
    os << formatString.substr(prevPos, currPos - prevPos);
    prevPos = currPos;
  }

  fmtstrng(os, formatString, prevPos, currPos, t);
}

template<typename T, typename... Params>
extern void fmtstrng(ostringstream& os, const string &formatString, size_t& prevPos, size_t& currPos, const T& t, const Params&... params) {
  if (currPos == string::npos) {
    throw std::invalid_argument("The format string contains LESS unescaped % symbols, than arguments");
    return;
  } else if (currPos == prevPos) {
    // then the char at the currFoundPos, was a %
    prevPos = currPos + 1;
    currPos = formatString.find('%', prevPos);
    if (prevPos == currPos) {
      // it's a double
      prevPos = currPos + 1;
      currPos = formatString.find('%', prevPos);
      os << '%';
    } else {
      // output t
      os << t;
      fmtstrng(os, formatString, prevPos, currPos, params...);
      return;
    }
  } else {
    // the first char was not a %
    os << formatString.substr(prevPos, currPos - prevPos);
    prevPos = currPos;
  }

  fmtstrng(os, formatString, prevPos, currPos, t, params...);
}

// Will insert parameters in the place of % in the format string, and deal with escaped %%
template<typename... Args>
extern string formatString(const std::string &formatString, const Args&... args) {
  ostringstream os;
  size_t prev = 0;
  size_t curr = formatString.find('%', prev);
  fmtstrng(os, formatString, prev, curr, args...);
  return os.str();
}

// Will print escaped strings without parameters, and error if a parameter was expected
static string formatString(const std::string &formatString) {
  ostringstream os;
  size_t prev = 0;
  size_t curr = formatString.find('%', prev);
  escapestrng(os, formatString, prev, curr);
  return os.str();
}

}
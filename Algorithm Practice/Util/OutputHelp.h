#pragma once

#include <ostream>
#include <tuple>
#include <vector>

namespace Util {

template <typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& vec) {
  if (vec.size() == 0) {
    o << "{ }";
    return o;
  }

  o << "{ ";
  for (int i = 0; i < vec.size() - 1; i++) {
    o << vec[i] << ", ";
  }

  o << vec[vec.size() - 1] << " }";

  return o;
}

template <typename T>
std::ostream& operator<<(std::ostream& o, const std::pair<T, T>& p) {
  o << "{ " << p.first << ", " << p.second << " }";
  return o;
}

}  // namespace Util

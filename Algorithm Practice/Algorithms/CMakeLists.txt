# Algorithms depends on DataStructures and Util
# TODO: in the future the dependency of Util could be decided by a flag

set(
  SOURCES 
  0000-Test.cpp
  0001-AddTwoNumbers.cpp
  0002-LongestCommonSubstr1Char.cpp
  0003-CoinChange.cpp
  0004-SmallestSubstrWithSameOrder.cpp
  0005-RotateRightByK.cpp
)

# add the Util library
add_subdirectory("../Util" Util)
list(APPEND EXTRA_LIBS Util)

# add the DataStructures library
add_subdirectory("../DataStructures" DataStructures)
list(APPEND EXTRA_LIBS DataStructures)

add_library(Algorithms ${SOURCES})

# state that anybody linking to us needs to include the current source dir
target_include_directories(
  Algorithms
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

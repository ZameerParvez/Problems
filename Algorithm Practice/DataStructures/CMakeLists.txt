# DataStructures only includes files in this directory

add_library(
  DataStructures INTERFACE
)

# add the Util library
add_subdirectory(../Util Util)

# state that anybody linking to us needs to include the current source dir
target_include_directories(
  DataStructures
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

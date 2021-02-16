# Util only includes files in this directory

if (NOT TARGET Util)
  add_library(Util INTERFACE)
endif()

# state that anybody linking to us needs to include the current source dir
target_include_directories(
  Util
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)


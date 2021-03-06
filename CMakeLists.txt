# This project cmake should include Algorithms, the other ones should be included at the same time

cmake_minimum_required(VERSION 3.16)

# set the project name and version
project(Problems VERSION 1.0)

add_library(algo_compiler_flags INTERFACE)
target_compile_features(algo_compiler_flags INTERFACE cxx_std_17)

# TODO: improve use of compiler flags, for realease and debug builds
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(algo_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

list(APPEND EXTRA_LIBS algo_compiler_flags)

# configure_file(Algoconfig.h.in Algoconfig.h)

# add the Algorithms library
add_subdirectory("Algorithms")
list(APPEND EXTRA_LIBS Algorithms)

# define a list of source files to compiled, so that they can be linked to the main target as a library
# target_link_libraries(algos PUBLIC algo_compiler_flags)



add_executable(Problems Main.cpp)
target_link_libraries(Problems PUBLIC ${EXTRA_LIBS})

# add the binary tree to the search path for include files, so Algoconfig.h can be found
target_include_directories(
  Problems PUBLIC
  "${PROJECT_BINARY_DIR}" # this is included incase, we decide to use a configuration file which is generated by cmake
)


# Problems
## Overview
This repo is for my own learning purposes. It is a collection of algorithms, data structures, and any solutions to other problems, implemented in C++17, and includes some other utilities that I think could be useful in another project.

## How to Use
- There is a build script which can be executed, and does the following

      cmake -S . -B build
      make

- The compiled binary is currently called "Problems" and running it will print a help message explaining how to use the executable
- The help message currently printed is

      Example Useage:
      
      ./Problems <algorithm-id> <input-path> <output-path>

      <algorithm-id> should be a 4 digit code that matches the id of the algorithm that you want to run
      <input-path> is required, and the inputs should match the format of the sample inputs provided in the SampleInputs directory
      <Output-path> is optional, by default std out will be used

## Implementation Details
- The algorithms follow an interface, so that they can be chosen easily at run time

      int parseInput(istream& input)
      int solve(ostream& output)

- There is logging functionality available as a macro, which calls a variadic function to format the string, and a logger class
- There is also a timer that is available as a macro, which creates an object and times between the objects creation and destruction
- The timer and logger can be used with

      LOG(<log level>, <format string>, <arguments>...)
      TIMER(<message>)

## TODO
- [ ] Improve cmake files, so that there are more options
  - for optimisations, logging macros and debug/release builds
- [ ] Refactor algorithms, so that they also contain a useful function that can be run on the specific data types needed

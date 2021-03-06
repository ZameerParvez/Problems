#pragma once

#include <chrono>

#include "Logger.h"

// TODO: ENABLETIMER should be defined by some config at compile time, should also be dependant on MSGINFO not being 0
#define ENABLETIMER

#ifdef ENABLETIMER
  #define TIMER(message) \
  Util::Timer t { message }
#else
  #define TIMER(message)
#endif

namespace Util {

using std::chrono::time_point;

// not sure if high resolution clock or steady clock
using timerClockType = std::chrono::high_resolution_clock;

// This logs the time between the timers construction and destruction, so it is suitable for logging the amount of time a block of code takes to execute
class Timer {
 private:
  static const int loglevel = 10;
  time_point<timerClockType> starttime;
  const char* message;

 public:
  Timer(const char* m = "") : message{m} {
    starttime = timerClockType::now();
  }

  ~Timer() {
    auto dt = timerClockType::now() - starttime;
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(dt).count();
    LOG(loglevel, "% : % microseconds", message, duration);
  }
};

}  // namespace Util
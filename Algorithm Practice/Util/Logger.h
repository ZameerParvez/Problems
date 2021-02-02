#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "FormatString.h"

// TODO: get defenitions from cmake or cmake generated header file
// IDEA: instead of singleton logger it could be useful to have loggers for specific purposes, but I haven't thought much about how it would affect the use of the macros (the macro could be passed a logger to log too). Logger instances could be stored in a static vector, so that the logger could be recalled at another time, or use instances of templates
// IDEA: The logger isn't very useful if it only logs to a stream when the output operator is called, becasause there are occasions where the program could terminate before the log is output to the stream. I could log directly to a stream instead, which would involve changing the log call to take a ostream, and not store messages in a buffer. If I allowed logger instances this could be used to identify each logger.
// IDEA: make the format of the output delimited in some way, so that the logs could be easily searched, or converted to another format

// LOGSTDOUT determines if logs are output to stdout as well as being stored in the message buffer, an immediatley outputs logs to stdout when they are made
#define LOGSTDOUT

// LEVEL determines which level log messages will be logged, only messages less than LEVEL
#ifndef LEVEL
#define LEVEL 9999
#endif

// MSGINFO determines how much information should be logged
#ifndef MSGINFO
#define MSGINFO 1
#endif

// This isn't great because the code is still included at the places the macro is called, ideally there would be a check done by the preprocessor first, but I can't nest ifs in defines which makes it difficult to solve
#define LLCHECK(level) (level <= LEVEL)

#if MSGINFO == 0
  #define PRELOG(lid, level, fmt, args...)
#elif MSGINFO == 1
  #define PRELOG(lid, level, fmt, args...) \
  if (LLCHECK(level)) Util::Logger<lid>::log(level, Util::formatString(fmt, ## args))
#elif MSGINFO == 2
  #define PRELOG(lid, level, fmt, args...) \
  if (LLCHECK(level)) Util::Logger<lid>::log(level, __FILE__, __LINE__, Util::formatString(fmt, ## args))
#else
  #define PRELOG(lid, level, fmt, args...)
#endif

// default logger id is 0, so this will use the default logger, unless another loggerid is defined
// This works, but is not a standard in compilers, it is only in gcc
#define LOG(level, fmt, args...) PRELOG(0, level, fmt, ## args)

namespace Util {

using std::ostream;
using std::string;
using std::vector;

// IDEA: logmessage may no longer be needed, because I don't know how useful it is to keep logs in memory
struct LogMessage {
  string file{};
  int linenum = 0;
  int logLevel = 0;  // not really needed right now, but it could be useful for searching the log message and the abstraction of logmessage could also be useful
  string message;

  LogMessage(string message, int level) : logLevel{level}, message{message} {}
  LogMessage(const char* file, int line, string message, int level) : file{file}, linenum{line}, logLevel{level}, message{message} {}

  LogMessage(LogMessage& other) {  // move constructor
    message = std::move(other.message);
    logLevel = other.logLevel;
    linenum = other.linenum;
    file = std::move(other.file);

    message.clear();
  }

  LogMessage(const LogMessage& other) {  // copy constructor
    message = other.message;
    logLevel = other.logLevel;
    linenum = other.linenum;
    file = other.file;
  }

  friend ostream& operator<<(ostream& o, const LogMessage& m) {
    if (m.file != "") {
      o << "FILE: " << m.file << " | LINE: " << m.linenum << " | ";
    }
    o << "LL" << m.logLevel << " | " << m.message << '\n';
    return o;
  }
};

// Logging with this class should be mostly done through the LOG macro
// IDEA: keep index of loggers and names, so that they can be retrieved when writing messages, if messages are going to be kept in the future
template <unsigned LID>
class Logger {
 private:
  static inline std::vector<LogMessage> messages;  // a singleton logger would have only one array of messages

  Logger(){};

 public:
  static inline Logger& getLogger() {
    static Logger instance;
    return instance;
  }

  // Prefer to use the macro instead of this
  static void log(LogMessage& message) {
#ifdef LOGSTDOUT
    std::cout << message;
#endif
    messages.push_back(std::move(message));
  }

  static void log(int loglevel, const string& message) {
    auto temp = LogMessage{message, loglevel};
#ifdef LOGSTDOUT
    std::cout << temp;
#endif
    messages.push_back(std::move(LogMessage{message, loglevel}));
  }

  // IDEA: maybe set an output stream to write to instead of a messages buffer, this way you could control where it outputs
  static void log(int loglevel, const char* file, int line, const string& message) {
    auto temp = LogMessage{file, line, message, loglevel};
#ifdef LOGSTDOUT
    std::cout << temp;
#endif
    messages.push_back(std::move(temp));
  }

  friend ostream& operator<<(ostream& o, const Logger<LID>& l) {
    o << "===== " << LID << " =====\n";
    auto& a = l.messages;  // could have also used singleton to access vector
    for (auto& m : a) {
      o << m;
    }

    return o;
  }
};

}  // namespace Util
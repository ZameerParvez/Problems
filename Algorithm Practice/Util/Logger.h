#pragma once

// TODO: get defenitions from cmake or cmake generated header file
// IDEA: instead of singleton logger it could be useful to have loggers for specific purposes, but I haven't thought much about how it would affect the use of the macros (the macro could be passed a logger to log too). Logger instances could be stored in a static vector, so that the logger could be recalled at another time
// IDEA: The logger isn't very useful if it only logs to a stream when the output operator is called, becasause there are occasions where the program could terminate before the log is output to the stream. I could log directly to a stream instead, which would involve changing the log call to take a ostream, and not store messages in a buffer. If I allowed logger instances this could be used to identify each logger.
// TODO: Implement the ideas above

// LOGSTDOUT determines if logs are output to stdout as well as being stored in the message buffer
// #define LOGSTDOUT

// LEVEL determines which level log messages will be logged, only messages less than LEVEL
#ifndef LEVEL
  #define LEVEL 9999
#endif

// MSGINFO determines how much information should be logged
#ifndef MSGINFO
  #define MSGINFO 1
#endif

#define LLCHECK(level) (level <= LEVEL)

// This isn't great because the code is still included at the places the macro is called, ideally there would be a check done by the preprocessor first, but I can't nest ifs in defines which makes it difficult to solve
#if MSGINFO == 0
  #define LOG(msg, level)
#elif MSGINFO == 1 
  #define LOG(msg, level) \
  if (LLCHECK(level)) Logger::log(toStringL(msg), level)
#elif MSGINFO == 2 
  #define LOG(msg, level) \
  if (LLCHECK(level)) Logger::log(__FILE__, __LINE__, toStringL(msg), level)
#else
  #define LOG(msg, level)
#endif

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using std::ostream;
using std::string;
using std::vector;
using std::ostringstream;

// IDEA: Could use variadics here to input more things
template<typename T>
string toStringL(const T& thing) {
  ostringstream os;
  os << thing;
  return os.str();
}

struct LogMessage {
  string file{};
  int linenum = 0;
  int logLevel = 0;  // not really needed right now, but it could be useful for searching the log message and the abstraction of logmessage could also be useful
  string message;

  LogMessage(string message, int level) : logLevel{level}, message{message} {}
  LogMessage(const char* file, int line, string message, int level) : file{file}, linenum{line}, logLevel{level}, message{message} {}

  LogMessage(LogMessage& other) { // move constructor
    message = std::move(other.message);
    logLevel = other.logLevel;
    linenum = other.linenum;
    file = std::move(other.file);

    message.clear();
  }

  LogMessage(const LogMessage& other) { // copy constructor
    message = other.message;
    logLevel = other.logLevel;
    linenum = other.linenum;
    file = other.file;
  }
  
  friend ostream& operator<<(ostream& o, const LogMessage& m);
};

// Logging with this class should be mostly done through the LOG macro
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

  static void log(const string& message, int loglevel = 0) {
    auto temp = LogMessage{message, loglevel};
  #ifdef LOGSTDOUT
    std::cout << temp;
  #endif
    messages.push_back(std::move(LogMessage{message, loglevel}));
  }

// IDEA: maybe set an output stream to write to instead of a messages buffer, this way you could control where it outputs
  static void log(const char* file, int line, const string& message, int loglevel = 0) {
    auto temp = LogMessage{file, line, message, loglevel};
  #ifdef LOGSTDOUT
    std::cout << temp;;
  #endif
    messages.push_back(std::move(temp));
  }

  friend ostream& operator<<(ostream& o, const Logger& l);
};


inline ostream& operator<<(ostream& o, const Logger& l) {
  auto& a = l.messages; // could have also used singleton to access vector
  for (auto& m : a) {
    o << m;
  }

  return o;
}

inline ostream& operator<<(ostream& o, const LogMessage& m) {
  if (m.file != "") {
    o << "FILE: " << m.file << " | LINE: " << m.linenum << " | ";
  }
  o << m.message << " | LL" << m.logLevel << '\n';
  return o;
}
#pragma once

#include <iostream>
#include <string>
#include <vector>

using std::ostream;
using std::string;
using std::vector;

struct LogMessage {
  int logLevel = 0;  // not really needed right now, but it could be useful for searching the log message and the abstraction of logmessage could also be useful
  string message;

  LogMessage(string message, int level):logLevel{level}, message{message} {}

  LogMessage(LogMessage& other) { // move constructor
    message = std::move(other.message);
    logLevel = other.logLevel;
    message.clear();
  }

  LogMessage(const LogMessage& other) { // copy constructor
    message = other.message;
    logLevel = other.logLevel;
  }
  
  friend ostream& operator<<(ostream& o, const LogMessage& m);

  // LogMessage& operator=(LogMessage&& other) {
  //   message = std::move(other.message);
  //   logLevel = other.logLevel;
  //   message.clear();
  //   return *this;
  // }
};

class Logger {
 private:
  static inline std::vector<LogMessage> messages;  // a singleton logger would have only one array of messages
  Logger(){};

 public:
  
  static inline Logger& getLogger() {
    static Logger instance;
    return instance;
  }

  static void log(LogMessage& message) {
    messages.push_back(std::move(message));
  }

  static void log(string& message, int loglevel = 0) {
    // LogMessage a{loglevel,message};
    messages.push_back(std::move(LogMessage{message, loglevel}));
  }

  static void log(const char* message, int loglevel = 0) {
    // LogMessage a{loglevel,message};
    messages.push_back(std::move(LogMessage{message, loglevel}));
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
  o << m.message << " : LL" << m.logLevel << '\n';
  return o;
}
#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <vector>

enum LogType { INFO, WARNING, ERROR };

struct LogEntry {
  LogType type;
  std::string message;
};

class Logger {
 public:
  static std::vector<LogEntry> allLogs;
  static void info(const std::string message);
  static void err(const std::string message);
};

#endif
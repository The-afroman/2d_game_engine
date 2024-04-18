#include "logger.h"
#include <ctime>
#include <format>
#include <iostream>
#include <string>

std::vector<LogEntry> Logger::allLogs;

void getDateTime(char *tbuffer, int tbuffSize) {
  // current date/time based on current system
  time_t now = time(0);
  // convert now to string form
  tm *gmtm = gmtime(&now);
  strftime(tbuffer, tbuffSize, "%F %XUTC", gmtm);
}

void Logger::info(const std::string message) {
  char datetime[40];
  getDateTime(datetime, 40);
  std::string lmessage = std::format("INFO: {} - {}", datetime, message);
  LogEntry entry;
  entry.type = INFO;
  entry.message = lmessage;
  allLogs.push_back(entry);
  std::cout << entry.message << std::endl;
}

void Logger::err(const std::string message) {
  char datetime[40];
  getDateTime(datetime, 40);
  std::string lmessage =
      std::format("\033[93mERR:  {} - {}\033[0m", datetime, message);
  LogEntry entry;
  entry.type = ERROR;
  entry.message = lmessage;
  allLogs.push_back(entry);
  std::cerr << entry.message << std::endl;
}
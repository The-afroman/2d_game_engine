#include <string>
#include <iostream>
#include <ctime>
#include <format>
#include "logger.h"

void Logger::info(const std::string message)
{
    // current date/time based on current system
    time_t now = time(0);
    // convert now to string form
    tm *gmtm = gmtime(&now);
    char tbuffer [40];
    strftime(tbuffer,40,"%F %XUTC", gmtm);
    std::cout << std::format("INFO: {} - {}",
                            tbuffer,
                            message)
              << std::endl;
}

void Logger::err(const std::string message)
{
    // current date/time based on current system
    time_t now = time(0);
    // convert now to tm struct for UTC
    tm *gmtm = gmtime(&now);
    char tbuffer [40];
    strftime(tbuffer,40,"%F %XUTC", gmtm);
    std::cerr << std::format("\033[93mERR:  {} - {}\033[0m",
                            tbuffer,
                            message)
              << std::endl;
}
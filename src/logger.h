#ifndef LOGGER_H
#define LOGGER_H
#include <string>

class Logger {
    public:
        static void info(const std::string message);
        static void err(const std::string message);

    private:
};

#endif
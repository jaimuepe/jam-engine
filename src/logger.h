#ifndef LOG_H
#define LOG_H

#include <spdlog/spdlog.h>

#include <iostream>

class Logger {

public:

    static const Logger& instance();

    template<typename T>
    void debug(const T& msg) const
    {
        spdlog::debug(msg);
    }

    template<typename T>
    void warn(const T& msg) const
    {
        spdlog::warn(msg);
    }

    template<typename T>
    void error(const T& msg) const
    {
        spdlog::error(msg);
    }

    template<typename T>
    void fatal(const T& msg) const
    {
        spdlog::critical(msg);
    }

private:
    Logger();
    Logger(const Logger&) = default;
    Logger& operator=(const Logger&) = default;
};

#endif // LOG_H

#ifndef LOGGER_H
#define LOGGER_H

#include "spdlog/spdlog.h"

namespace logging
{

namespace level
{

enum level_enum
{
    trace = 0,
    debug = 1,
    info = 2,
    warn = 3,
    error = 4,
    critical = 5,
    off = 6
};

} // namespace level

inline void setLevel(level::level_enum level)
{
    spdlog::set_level(static_cast<spdlog::level::level_enum>(level));
}

inline void setupLogger()
{
    setLevel(level::debug);
}

template<typename T>
inline void trace(const T &msg)
{
     spdlog::trace(msg);
}

template<typename T>
inline void debug(const T& msg)
{
    spdlog::debug(msg);
}

template<typename T>
inline void warn(const T& msg)
{
    spdlog::warn(msg);
}

template<typename T>
inline void error(const T& msg)
{
    spdlog::error(msg);
}

template<typename T>
inline void fatal(const T& msg)
{
    spdlog::critical(msg);
}

} // namespace logging

#endif // LOGGER_H

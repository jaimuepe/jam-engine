
#include "logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

Logger::Logger()
{
    spdlog::set_level(spdlog::level::debug);
}

const Logger& Logger::instance()
{
    static const Logger instance;
    return instance;
}

#include "Logger.h"

#include <sstream>
#include <cstdarg>


hive::Logger::Logger(std::vector<Sink *> &sinks)
{
    sinks_ = std::move(sinks);
}

void hive::Logger::log(LogLevel level, const char *msg, ...) const
{
    std::stringstream ss;
    va_list args;
    va_start(args, msg);
    char buf[1024]; // Temporary buffer to hold the formatted message
    vsnprintf(buf, sizeof(buf), msg, args);
    ss << buf;
    const std::string out = ss.str();
    va_end(args);
    for(const auto sink : sinks_)
    {
        sink->log(level, out.c_str());
    }
}



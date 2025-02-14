#include "Logger.h"
#include <iostream>
#include <cstdarg>


hive::Logger& hive::Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void hive::Logger::Log(LogLevel level, const char *message, ...)
{
    char buffer[1024];

    va_list args;
    va_start(args, message);
    vsnprintf(buffer, 1024, message, args);
    va_end(args);

    for (auto &callback : callbacks_)
    {
        callback(level, std::string(buffer));
    }
}

void hive::Logger::AddCallback(LoggerCallback callback)
{
    callbacks_.push_back(callback);
}

hive::Logger::Logger()
{
    AddDefaultCallback();
}

void hive::Logger::AddDefaultCallback()
{
    //TODO: add a better default callback with color and prefix
    AddCallback([](LogLevel level, const std::string &message)
    {
        std::cout << message << std::endl;
    });
}

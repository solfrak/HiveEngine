#include "Logger.h"
#include <iostream>



hive::Logger& hive::Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void hive::Logger::Log(LogLevel level, const std::string &message, ...)
{
    for (auto &callback : callbacks_)
    {
        callback(level, message);
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

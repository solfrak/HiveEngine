//
// Created by samuel on 9/11/24.
//
#include "Logger.h"

#include "Debug/Profiler.h"

URef<hive::Logger> hive::Logger::s_instance = nullptr;

void hive::Logger::init(Logger *logger) {
    TRACE_EVENT("engine", "Logger::init");
    s_instance = std::unique_ptr<Logger>(logger);
}

void hive::Logger::shutdown()
{
    TRACE_EVENT("engine", "Logger::shutdown");
    s_instance.reset();
}

void hive::Logger::log(const std::string &msg, const LogLevel level) {
    TRACE_EVENT("engine", "Logger::log");
    if(s_instance == nullptr)
    {
        return;
    }
    s_instance->logImpl(msg, level);
}

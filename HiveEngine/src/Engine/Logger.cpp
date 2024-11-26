//
// Created by samuel on 9/11/24.
//
#include "Logger.h"

#include "Debug/Profiler.h"

URef<hive::Logger> hive::Logger::s_instance = nullptr;

void hive::Logger::init(Logger *logger) {
    HPROFILE_FUNCTION();
    s_instance = std::unique_ptr<Logger>(logger);
}

void hive::Logger::shutdown()
{
    HPROFILE_FUNCTION();
    s_instance.reset();
}

void hive::Logger::log(const std::string &msg, const LogLevel level) {
    HPROFILE_FUNCTION();
    if(s_instance == nullptr)
    {
        return;
    }
    s_instance->logImpl(msg, level);
}

#include <Engine/Logger.h>
#include <Debug/Profiler.h>

static hive::Logger* g_instance = nullptr;

void hive::Logger::init(Logger *logger) {
    HPROFILE_TRACE_EVENT("engine", "Logger::init");
    g_instance = logger;
}

void hive::Logger::shutdown()
{
    HPROFILE_TRACE_EVENT("engine", "Logger::shutdown");
    delete g_instance;
    g_instance = nullptr;
}

void hive::Logger::log(const std::string &msg, const LogLevel level) {
    HPROFILE_TRACE_EVENT("engine", "Logger::log");
    if(g_instance == nullptr)
    {
        return;
    }
    g_instance->logImpl(msg, level);
}

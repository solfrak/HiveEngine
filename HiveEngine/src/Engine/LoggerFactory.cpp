
#include <Engine/LoggerFactory.h>
#include <Engine/ConsoleLogger.h>
#include <Engine/FileLogger.h>
#include <Debug/Profiler.h>


hive::ConsoleLogger* createConsoleLogger() {
    HPROFILE_TRACE_EVENT("engine", "createConsoleLogger");
    return new hive::ConsoleLogger();
}

const char* LOG_FILE_OUTPUT = "log.txt";

hive::FileLogger* createFileLogger() {
    HPROFILE_TRACE_EVENT("engine", "createFileLogger");
    return new hive::FileLogger(LOG_FILE_OUTPUT);
}


hive::Logger* hive::LoggerFactory::Create(LogOutputType type)
{
    HPROFILE_TRACE_EVENT("engine", "Create");
    switch (type) {
        case LogOutputType::File:
            return createFileLogger();
        case LogOutputType::Console:
        default:
            return createConsoleLogger();
    }

}

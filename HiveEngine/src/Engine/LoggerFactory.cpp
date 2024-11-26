//
// Created by samuel on 9/1/24.
//

#include "LoggerFactory.h"

#include "ConsoleLogger.h"
#include "FileLogger.h"
#include "Debug/Profiler.h"
const char* LOG_FILE_OUTPUT = "log.txt";

hive::ConsoleLogger* createConsoleLogger() {
    HPROFILE_FUNCTION();
    return new hive::ConsoleLogger();
}

hive::FileLogger* createFileLogger() {
    HPROFILE_FUNCTION();
    return new hive::FileLogger(LOG_FILE_OUTPUT);
}


hive::Logger* hive::LoggerFactory::Create(LogOutputType type)
{
    HPROFILE_FUNCTION();
    switch (type) {
        case LogOutputType::File:
            return createFileLogger();
        case LogOutputType::Console:
        default:
            return createConsoleLogger();
    }

}

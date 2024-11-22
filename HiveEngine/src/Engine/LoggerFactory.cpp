//
// Created by samuel on 9/1/24.
//

#include "LoggerFactory.h"

#include "ConsoleLogger.h"
#include "FileLogger.h"
const char* LOG_FILE_OUTPUT = "log.txt";

hive::ConsoleLogger* createConsoleLogger() {
    return new hive::ConsoleLogger();
}

hive::FileLogger* createFileLogger() {
    return new hive::FileLogger(LOG_FILE_OUTPUT);
}


hive::Logger* hive::LoggerFactory::Create(LogOutputType type)
{
    switch (type) {
        case LogOutputType::File:
            return createFileLogger();
        case LogOutputType::Console:
        default:
            return createConsoleLogger();
    }

}

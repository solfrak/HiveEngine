//
// Created by samuel on 8/29/24.
//

#include "ConsoleLogger.h"

namespace hive {
    ConsoleLogger::ConsoleLogger() {
    }

    ConsoleLogger::~ConsoleLogger() {
        // logImpl("Closing the console logger", LogLevel::Info);
    }

    void ConsoleLogger::logImpl(const std::string &msg, LogLevel level) {
        setLogLevelColor(level);
        std::cout << msg;
        resetColor();
    }

    bool ConsoleLogger::isCorrect() {
        return true;
    }


} // hive
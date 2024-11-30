#include <Engine/ConsoleLogger.h>

namespace hive {
    void ConsoleLogger::logImpl(const std::string &msg, LogLevel level) 
    {
        setLogLevelColor(level);
        std::cout << msg;
        resetColor();
    }

    bool ConsoleLogger::isCorrect() 
    {
        return true;
    }


} // hive
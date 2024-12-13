#include "ConsoleSink.h"

#include <iostream>

hive::ConsoleSink::ConsoleSink(const LogLevel level): level_(level)
{

}

void hive::ConsoleSink::log(const LogLevel level, const char *msg)
{
    //TODO change terminal color (platfom specific)
    if(level >= level_)
    {
        switch (level)
        {
            case LogLevel::DEBUG:
                std::cout << "[DEBUG] " << msg << std::endl;
                break;
            case LogLevel::INFO:
                std::cout << "[INFO] " << msg << std::endl;
                break;
            case LogLevel::WARN:
                std::cout << "[WARN] " << msg << std::endl;
                break;
            case LogLevel::ERROR:
                std::cout << "[ERROR] " << msg << std::endl;
                break;
        }
    }
}

#pragma once

#include <Engine/Logger.h>

namespace hive {

    class ConsoleLogger final : public Logger 
    {
    public:
        ConsoleLogger() = default;
        ~ConsoleLogger() = default;

        [[nodiscard]] bool isCorrect() override;
    private:

        //Those function is platform specific, it's implementation should be located in platform_console_logger.cpp
        static void setLogLevelColor(LogLevel level);
        static void resetColor();

    protected:
        void logImpl(const std::string &msg, LogLevel level) override;

    public:
    };


} // hive


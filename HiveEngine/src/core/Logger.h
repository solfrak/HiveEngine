#pragma once

#include <hvpch.h>
#include <vector>
#include <functional>
#include <string>
namespace hive
{
    enum class LogLevel
    {
        Debug, Info, Warn, Error
    };

    using LoggerCallback = std::function<void(LogLevel, std::string)>;

    class Logger
    {
    public:
        static Logger& getInstance(); //Lazy loading singleton

        void Log(LogLevel level, const char* message, ...);
        void AddCallback(LoggerCallback callback);

        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger(Logger&&) = delete;
    private:
        Logger();
        void AddDefaultCallback();

    protected:
        std::vector<LoggerCallback> callbacks_;
    };

}
#define LOG_DEBUG(msg, ...) hive::Logger::getInstance().Log(hive::LogLevel::Debug, msg, ##__VA_ARGS__);
#define LOG_INFO(msg, ...) hive::Logger::getInstance().Log(hive::LogLevel::Info, msg, ##__VA_ARGS__);
#define LOG_WARN(msg, ...) hive::Logger::getInstance().Log(hive::LogLevel::Warn, msg, ##__VA_ARGS__);
#define LOG_ERROR(msg, ...) hive::Logger::getInstance().Log(hive::LogLevel::Error, msg, ##__VA_ARGS__);

//
// Created by samuel on 8/29/24.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <hvpch.h>

namespace hive {
    enum class LogLevel {
        Debug, Info, Warning, Error, Fatal
    };

    class HAPI Logger {
    public:
        virtual ~Logger() = default;

        static void init(Logger* logger);
        static void shutdown();
        static void log(const std::string &msg, LogLevel level);
        virtual bool isCorrect() = 0;

    protected:
        virtual void logImpl(const std::string &msg, LogLevel level) = 0;

    private:
        static URef<Logger> s_instance;
    };

} // hive

//We want to log Fatal and Error message no mather the reason
#define HLOG_FATAL(msg) hive::Logger::log(msg, hive::LogLevel::Fatal)
#define HLOG_ERROR(msg) hive::Logger::log(msg, hive::LogLevel::Error)


//Other level of logging can be customized
#define HLOG_WARN_ENABLED
#ifdef HLOG_WARN_ENABLED
#define HLOG_WARN(msg) hive::Logger::log(msg, hive::LogLevel::Warning)
#else
#define HLOG_WARN(msg)
#endif

#define HLOG_INFO_ENABLED
#ifdef HLOG_INFO_ENABLED
#define HLOG_INFO(msg) hive::Logger::log(msg, hive::LogLevel::Info)
#else
#define HLOG_INFO(msg)
#endif

#define HLOG_DEBUG_ENABLED
#ifdef HLOG_DEBUG_ENABLED
#define HLOG_DEBUG(msg) hive::Logger::log(msg, hive::LogLevel::Debug)
#else
#define HLOG_DEBUG(msg)
#endif


#endif //LOGGER_H

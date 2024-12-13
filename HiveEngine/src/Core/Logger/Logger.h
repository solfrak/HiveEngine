#pragma once

#include <vector>
namespace hive
{
    enum class LogLevel
    {
        DEBUG, INFO, WARN, ERROR
    };


    class Sink
    {
    public:
        virtual ~Sink() = default;
        virtual void log(LogLevel level, const char* msg) = 0;
    };

    class Logger
    {
    public:
        explicit Logger(std::vector<Sink*> &sinks);
        void log(LogLevel level, const char* msg, ...) const;

    private:
        std::vector<Sink*> sinks_;
    };

}

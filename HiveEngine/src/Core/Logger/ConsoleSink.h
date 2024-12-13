#pragma once
#include "Logger.h"

namespace hive
{
    class ConsoleSink : public Sink
    {
    public:
        explicit ConsoleSink(LogLevel level);
        void log(LogLevel level, const char *msg) override;

    private:
        LogLevel level_;
    };
}

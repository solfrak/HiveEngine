#pragma once

#include <hvpch.h>

namespace hive 
{
	class Logger;

    enum class LogOutputType {
        Console, File
    };

    class HAPI LoggerFactory {
    public:
        static Logger* Create(LogOutputType type);
    };

}

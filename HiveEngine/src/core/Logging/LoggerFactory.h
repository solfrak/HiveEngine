//
// Created by samuel on 9/1/24.
//

#ifndef LOGGINGFACTORY_H
#define LOGGINGFACTORY_H

#include "Logger.h"

#include <hvpch.h>

namespace hive {

    enum class LogOutputType {
        Console, File
    };

    class HAPI LoggerFactory {
    public:
        static Logger* createLogger(LogOutputType type);
    };

}



#endif //LOGGINGFACTORY_H

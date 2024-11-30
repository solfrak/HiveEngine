//
// Created by samuel on 8/30/24.
//

#include "FileLogger.h"

#include "Debug/Profiler.h"

namespace hive {
    FileLogger::FileLogger(const std::string &filePath) {
        TRACE_EVENT("engine", "FileLogger::FileLogger");
        m_fileStream = std::ofstream(filePath, std::ios::out | std::ios::app);
        if (!m_fileStream.is_open())
        {
            //ERROR LOG HERE
        }
    }

    FileLogger::~FileLogger() {
        TRACE_EVENT("engine", "FileLogger::~FileLogger");
        m_fileStream.close();
    }

    void FileLogger::logImpl(const std::string &msg, LogLevel level) {
        TRACE_EVENT("engine", "FileLogger::logImpl");
        m_fileStream << msg << std::endl;
    }

    bool FileLogger::isCorrect() {
        TRACE_EVENT("engine", "FileLogger::isCorrect");
        return m_fileStream.is_open();
    }
} // hive
//
// Created by samuel on 8/30/24.
//

#include "FileLogger.h"

#include "Debug/Profiler.h"

namespace hive {
    FileLogger::FileLogger(const std::string &filePath) {
        HPROFILE_FUNCTION();
        m_fileStream = std::ofstream(filePath, std::ios::out | std::ios::app);
        if (!m_fileStream.is_open())
        {
            //ERROR LOG HERE
        }
    }

    FileLogger::~FileLogger() {
        HPROFILE_FUNCTION();
        m_fileStream.close();
    }

    void FileLogger::logImpl(const std::string &msg, LogLevel level) {
        HPROFILE_FUNCTION();
        m_fileStream << msg << std::endl;
    }

    bool FileLogger::isCorrect() {
        HPROFILE_FUNCTION();
        return m_fileStream.is_open();
    }
} // hive
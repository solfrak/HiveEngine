#include <Engine/FileLogger.h>
#include <Debug/Profiler.h>

namespace hive 
{
    FileLogger::FileLogger(const std::string &filePath) 
    {
        HPROFILE_TRACE_EVENT("engine", "FileLogger::FileLogger");
        m_fileStream = std::ofstream(filePath, std::ios::out | std::ios::app);
        if (!m_fileStream.is_open())
        {
            HLOG_ERROR("Could not open the requested file for logging");
        }
    }

    FileLogger::~FileLogger() 
    {
        HPROFILE_TRACE_EVENT("engine", "FileLogger::~FileLogger");
        m_fileStream.close();
    }

    void FileLogger::logImpl(const std::string &msg, LogLevel level) 
    {
		HPROFILE_TRACE_EVENT("engine", "FileLogger::logImpl");
        m_fileStream << msg << std::endl;
    }

    bool FileLogger::isCorrect() 
    {
        HPROFILE_TRACE_EVENT("engine", "FileLogger::isCorrect");
        return m_fileStream.is_open();
    }
} // hive
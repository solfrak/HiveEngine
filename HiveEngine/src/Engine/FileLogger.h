#pragma once
#include <Engine/Logger.h>

#include <fstream>
#include <string>

namespace hive {
    class FileLogger final : public Logger 
	{
	public:
        explicit FileLogger(const std::string &filePath);

        ~FileLogger() override;

        [[nodiscard]] bool isCorrect() override;

    protected:
        void logImpl(const std::string &msg, LogLevel level) override;

    private:
        std::ofstream m_fileStream;
    };

} // hive


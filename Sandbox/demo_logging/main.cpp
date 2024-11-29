#include <iostream>

#include "Engine/Logger.h"
#include "Engine/LoggerFactory.h"

#include <Engine/Application.h>
hive::Application* CreateApplication()
{
 	return nullptr;
}

int main()
{
	hive::Logger::init(hive::LoggerFactory::Create(hive::LogOutputType::Console));
	HLOG_FATAL("FATAL Message");
	HLOG_ERROR("ERROR Message");
	HLOG_WARN("WARNING Message");
	HLOG_INFO("INFO Message");
	HLOG_DEBUG("DEBUG Message");
	hive::Logger::shutdown();

	//All the log will be output in a file called log.txt
	// hive::Logger::init(hive::LoggerFactory::createLogger(hive::LogOutputType::File));
	// HLOG_FATAL("FATAL Message");
	// HLOG_ERROR("ERROR Message");
	// HLOG_WARN("WARNING Message");
	// HLOG_INFO("INFO Message");
	// HLOG_DEBUG("DEBUG Message");
	// hive::Logger::shutdown();
}

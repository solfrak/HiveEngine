//
// Created by samuel on 11/17/24.
//
#include <core/Debug/Asserts.h>
#include <core/Logging/Logger.h>
#include "core/Logging/LoggerFactory.h"

int main()
{
	hive::Logger::init(hive::LoggerFactory::createLogger(hive::LogOutputType::Console));
	int x = 0;

	//Will check if the condition is true. If not, will log where the assertion failed. When debugging the application, will debug break at this point
	HASSERTS(x == 1);

	HLOG_INFO("Terminating application");
}

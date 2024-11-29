//
// Created by samuel on 11/17/24.
//
#include <Debug/Asserts.h>
#include <Engine/Logger.h>
#include "Engine/LoggerFactory.h"

#include <Engine/Application.h>
hive::Application* CreateApplication()
{
 	return nullptr;
}

int main()
{
	hive::Logger::init(hive::LoggerFactory::Create(hive::LogOutputType::Console));
	int x = 0;

	//Will check if the condition is true. If not, will log where the assertion failed. When debugging the application, will debug break at this point
	HASSERTS(x == 1);

	HLOG_INFO("Terminating application");
}

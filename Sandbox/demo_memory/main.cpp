//
// Created by samuel on 11/17/24.
//
#include <core/Logging/Logger.h>
#include <core/Logging/LoggerFactory.h>

#include <core/Memory/Memory.h>

struct MyStruct
{
	int x, y, z;
};
int main()
{
	hive::Logger::init(hive::LoggerFactory::createLogger(hive::LogOutputType::Console));

	MyStruct* mystruct = static_cast<MyStruct*>(hmalloc(sizeof(MyStruct)));
	mystruct->x = 10;

	hfree(sizeof(MyStruct), mystruct);
}

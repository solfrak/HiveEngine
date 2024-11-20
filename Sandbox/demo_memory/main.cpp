//
// Created by samuel on 11/17/24.
//
#include <Core/Logging/Logger.h>
#include <Core/Logging/LoggerFactory.h>

#include <Core/Memory/Memory.h>

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

//
// Created by samuel on 11/17/24.
//
#include <Engine/Logger.h>
#include <Engine/LoggerFactory.h>

#include <Ressource/Memory.h>

#include <Engine/Application.h>
hive::Application* CreateApplication()
{
 	return nullptr;
}

struct MyStruct
{
	int x, y, z;
};
int main()
{
	hive::Logger::init(hive::LoggerFactory::Create(hive::LogOutputType::Console));

	MyStruct* mystruct = static_cast<MyStruct*>(hmalloc(sizeof(MyStruct)));
	mystruct->x = 10;

	hfree(sizeof(MyStruct), mystruct);
}

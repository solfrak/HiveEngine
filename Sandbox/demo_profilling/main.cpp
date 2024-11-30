//
// Created by samuel on 11/13/24.
//

#include "Debug/Profiler.h"
#include "Engine/Application.h"
#include <thread>

//Not used. Just to no have compiler error
hive::Application* CreateApplication()
{
 	return nullptr;
}


void otherLongRunningFunction()
{
	HPROFILE_TRACE_EVENT("engine", "otherLongRunningFunction");
	std::this_thread::sleep_for(std::chrono::seconds(2));
}
void longRunningFunction()
{
	HPROFILE_TRACE_EVENT("engine", "longRunningFunction");
	otherLongRunningFunction();
	std::this_thread::sleep_for(std::chrono::seconds(1));
}



int main(int argc, char** argv)
{
	HPROFILE_BEGIN_SESSION();
	longRunningFunction();
	otherLongRunningFunction();
	HPROFILE_END_SESSION();
}

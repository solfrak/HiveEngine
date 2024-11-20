//
// Created by samuel on 11/13/24.
//

#include "Core/Debug/Profiler.h"

void otherLongRunningFunction()
{
	HPROFILE_FUNCTION();
	std::this_thread::sleep_for(std::chrono::seconds(2));
}
void longRunningFunction()
{
	HPROFILE_FUNCTION();
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
//
// Created by samuel on 11/17/24.
//
#include "Asserts.h"
#include "core/Logging/Logger.h"

void reportAssert(const char* expression, const char* file, int line)
{
	std::string msg;
	msg += "Assertion failed: ";
	msg += expression;
	msg += "\nFile: ";
	msg += file;
	msg += "\nLine: ";
	msg += std::to_string(line) + "\n";
	HLOG_FATAL(msg);
}

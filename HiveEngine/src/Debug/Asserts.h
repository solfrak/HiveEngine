//
// Created by samuel on 11/17/24.
//

#pragma once
#include "hvpch.h"


HAPI void reportAssert(const char* expression, const char* file, int line);


#define HASSETS_ENABLED
#ifdef HASSETS_ENABLED

#ifdef _MSC_VER
#define HDEBUG_BREAK() __debugbreak()
#else
#define HDEBUG_BREAK() __builtin_trap()
#endif

#define HASSERTS(expression) \
	if(!(expression)) { reportAssert(#expression, __FILE__, __LINE__); HDEBUG_BREAK(); }

#else
#define HASSERTS(value)
#endif
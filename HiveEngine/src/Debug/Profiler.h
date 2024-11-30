//
// Created by samuel on 11/29/24.
//

#pragma once
#include "hvpch.h"

#define PROFILER_ENABLED
#include <perfetto.h>
PERFETTO_DEFINE_CATEGORIES(
	perfetto::Category("rendering")
		.SetDescription("Rendering and graphics events"),
	perfetto::Category("engine")
		.SetDescription("Engine events"),
	perfetto::Category("game")
		.SetDescription("game logic event"),
	perfetto::Category("memory"),

);

#ifdef PROFILER_ENABLED

namespace hive::profiler
{
	void HAPI InitPerfetto();
	void HAPI EndPerfetto();
}

//Define some tracing categories


#define HPROFILE_BEGIN_SESSION() hive::profiler::InitPerfetto();
#define HPROFILE_END_SESSION() hive::profiler::EndPerfetto();
#define HPROFILE_TRACE_EVENT(category, name, ...) TRACE_EVENT(category, name, __VA_ARGS__)

#else
#define HPROFILE_BEGIN_SESSION()
#define HPROFILE_END_SESSION()
#define HPROFILE_TRACE_EVENT(category, name, ...)
#endif



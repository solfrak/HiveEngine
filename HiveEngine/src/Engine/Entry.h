#pragma once
#include "Application.h"
#include "Engine.h"
#include "Debug/Profiler.h"

hive::Application* CreateApplication();

int main(int argc, char** argv)
{
	HPROFILE_BEGIN_SESSION();

	hive::Engine engine(argc, argv, CreateApplication());
	engine.run();

	HPROFILE_END_SESSION();
}

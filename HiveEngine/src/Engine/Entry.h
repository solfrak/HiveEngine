#pragma once

#include <Engine/Application.h>
#include <Engine/Engine.h>
#include <Debug/Profiler.h>

hive::Application* CreateApplication(hive::Engine &engine);

int main(int argc, char** argv)
{
	HPROFILE_BEGIN_SESSION();

	hive::Engine engine(argc, argv);
	hive::Application* application = CreateApplication(engine);
	engine.setApplication(application);
	engine.init();
	engine.run();

	HPROFILE_END_SESSION();
}

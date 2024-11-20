//
// Created by samuel on 11/13/24.
//
#include "Core/Windowing/Window.h"
#include "Core/Windowing/WindowManager.h"
#include "Core/Windowing/WindowFactory.h"

int main()
{
	hive::WindowConfiguration config;
	config.set(hive::WindowConfigurationOptions::RESIZABLE, true);
	hive::Window* window =  hive::WindowFactory::Create("HiveEngine", 800, 600, config);

	//WindowManager is a singleton that make it possible to access the Window across all the application
	// hive::WindowManager::setCurrentWindow(std::shared_ptr<hive::Window>(window));

	while(!window->shouldClose())
	{
		window->onUpdate();
	}
	delete window;
}

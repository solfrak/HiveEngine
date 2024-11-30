//
// Created by samuel on 11/13/24.
//
#ifdef HIVE_RAYLIB_ENABLED
#include <Engine/Window.h>
#include "raylib.h"
#include <Debug/Profiler.h>

void hive::Window::init(const char *title, int width, int height, WindowConfiguration config)
{
	TRACE_EVENT("engine", "WindowRaylib::WindowRaylib");
	InitWindow(width, height, title);

	//TODO: Handle all config
	if(config.has(WindowConfigurationOptions::RESIZABLE))
		SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(60);

	//Disable the ESC key to exit by default
	SetExitKey(0);
}

hive::Window::~Window()
{
	CloseWindow();
}

int hive::Window::getHeight() const
{
	return GetScreenWidth();
}

hive::WindowNativeData hive::Window::getNativeWindowData() const
{
	WindowNativeData windowNativeData;
	windowNativeData.backend = WindowNativeData::RAYLIB;
	windowNativeData.window_handle = GetWindowHandle();
	windowNativeData.sizeof_ptr = sizeof(Window);

	return windowNativeData;
}

int hive::Window::getWidth() const
{
	return GetScreenWidth();
}

void hive::Window::onUpdate() const
{
	// BeginDrawing();
	// EndDrawing();
}

void hive::Window::setIcon(unsigned char* data, int width, int height) const
{
	Image image;
	image.width = width;
	image.height = height;
	image.data = data;
	SetWindowIcon(image);
}

bool hive::Window::shouldClose() const
{
	return WindowShouldClose();
}

void hive::Window::updateConfiguration(WindowConfiguration configuration)
{
	m_config = configuration;
	//TODO: Handle changes
}

hive::WindowConfiguration hive::Window::getConfiguration() const
{
	return m_config;
}
#endif

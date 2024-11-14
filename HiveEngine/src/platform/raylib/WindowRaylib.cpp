//
// Created by samuel on 11/13/24.
//
#include "WindowRaylib.h"
#ifdef HIVE_RAYLIB_ENABLED
#include "raylib.h"

hive::WindowRaylib::WindowRaylib(const char* title, int width, int height, WindowConfiguration config)
{

	InitWindow(width, height, title);

	//TODO: Handle all config
	if(config.has(WindowConfigurationOptions::RESIZABLE))
		SetWindowState(FLAG_WINDOW_RESIZABLE);
}

hive::WindowRaylib::~WindowRaylib()
{
	CloseWindow();
}

int hive::WindowRaylib::getHeight() const
{
	return GetScreenWidth();
}

hive::WindowNativeData hive::WindowRaylib::getNativeWindowData() const
{
	WindowNativeData windowNativeData;
	windowNativeData.backend = WindowNativeData::RAYLIB;
	windowNativeData.window_handle = GetWindowHandle();

	return windowNativeData;
}

int hive::WindowRaylib::getWidth() const
{
	return GetScreenWidth();
}

void hive::WindowRaylib::onUpdate() const
{
	BeginDrawing();
	EndDrawing();
}

void hive::WindowRaylib::setIcon(unsigned char* data, int width, int height) const
{
	Image image;
	image.width = width;
	image.height = height;
	image.data = data;
	SetWindowIcon(image);
}

bool hive::WindowRaylib::shouldClose() const
{
	return WindowShouldClose();
}

void hive::WindowRaylib::updateConfiguration(WindowConfiguration configuration)
{
	m_config = configuration;
	//TODO: Handle changes
}

hive::WindowConfiguration hive::WindowRaylib::getConfiguration()
{
	return m_config;
}
#endif

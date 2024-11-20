//
// Created by samuel on 11/17/24.
//
#include "Application.h"

#include "raylib.h"
#include "Debug/Asserts.h"
#include "Logger.h"
#include "LoggerFactory.h"
#include <Ressource/Memory.h>
#include "Window.h"
#include "WindowFactory.h"

void (*application_init_ptr)(hive::Application&) = nullptr;
void (*application_tick_ptr)(hive::Application&) = nullptr;
void (*application_shutdown_ptr)(hive::Application&) = nullptr;
void (*application_config_ptr)(hive::Application&) = nullptr;


hive::Application::Application(void(*config)(Application&), void(*init)(Application &), void(*tick)(Application &), void(*shutdown)(Application &))
{
	application_config_ptr = config;
	application_init_ptr = init;
	application_tick_ptr = tick;
	application_shutdown_ptr = shutdown;

	Logger::init(LoggerFactory::createLogger(LogOutputType::Console));

	application_config_ptr(*this);

	WindowConfiguration window_configuration;
	m_window = WindowFactory::Create(m_config.title, m_config.width, m_config.height, window_configuration);

	m_renderer2D.init();
	m_renderer3D.init();

	application_init_ptr(*this);
}

hive::Application::~Application()
{
	application_shutdown_ptr(*this);

	m_renderer3D.shutdown();
	m_renderer2D.shutdown();

	auto window_data = m_window->getNativeWindowData();
	hfree(window_data.sizeof_ptr, m_window);

	Logger::shutdown();
}


void hive::Application::run()
{
	while(isRunning() && !m_window->shouldClose())
	{
		BeginDrawing();
		tick();
		EndDrawing();
	}
}

void hive::Application::tick()
{
	application_tick_ptr(*this);
}

bool hive::Application::isRunning() const
{
	return !terminated;
}

void hive::Application::setConfig(const ApplicationConfig& config)
{
	m_config = config;
}


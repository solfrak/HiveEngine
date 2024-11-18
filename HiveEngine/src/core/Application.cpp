//
// Created by samuel on 11/17/24.
//
#include "Application.h"

#include "Debug/Asserts.h"
#include "Logging/Logger.h"
#include "Logging/LoggerFactory.h"
#include "Memory/Memory.h"
#include "Windowing/Window.h"
#include "Windowing/WindowFactory.h"

hive::Application::Application()
{
	Logger::init(LoggerFactory::createLogger(LogOutputType::Console));
	application_init(*this);
	WindowConfiguration window_configuration;
	m_window = hive::WindowFactory::Create(m_config.title, m_config.width, m_config.height, window_configuration);
}

hive::Application::~Application()
{
	application_shutdown(*this);

	auto window_data = m_window->getNativeWindowData();
	hfree(window_data.sizeof_ptr, m_window);

Logger::shutdown();
}

void hive::Application::run()
{
	while(isRunning() && !m_window->shouldClose())
	{
		tick();
	}
}

void hive::Application::tick()
{
	application_tick(*this);
}

bool hive::Application::isRunning() const
{
	return !terminated;
}

void hive::Application::setConfig(const ApplicationConfig& config)
{
	m_config = config;
}

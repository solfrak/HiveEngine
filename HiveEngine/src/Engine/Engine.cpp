//
// Created by samuel on 11/22/24.
//

#include "Engine.h"

#include <thread>

#include "Logger.h"
#include "LoggerFactory.h"
#include "raylib.h"
#include "Debug/Profiler.h"
#include "Rendering/RenderCommand.h"

static hive::Engine* g_engine = nullptr;



hive::Engine::Engine(int argc, char **argv) : m_Application(nullptr)
{
	TRACE_EVENT("engine", "Engine::Engine");

	g_engine = this;
	//TODO: Parse the arguments
}

void hive::Engine::setApplication(Application *application)
{
	TRACE_EVENT("engine", "Engine::setApplication");
	m_Application = application;
}


void hive::Engine::run()
{
	TRACE_EVENT("engine", "Engine::run");
	while(m_Application->m_Running)
	{
		m_Application->onUpdate();

		//TODO: Abstract the usage of Raylib here
		RenderCommand::BeginFrame();
		m_Application->onRender();
		RenderCommand::EndFrame();
	}

	shutdown();
}

hive::Window& hive::Engine::get_window()
{
	TRACE_EVENT("engine", "Engine::get_window");
	return g_engine->m_Window;
}

hive::Application* hive::Engine::get_application()
{
	TRACE_EVENT("engine", "Engine::get_application");
	return g_engine->m_Application;
}

void hive::Engine::init()
{
	TRACE_EVENT("engine", "Engine::init");
	//TODO: Default is console, Switch to other type based on argument if defined
	Logger::init(LoggerFactory::Create(LogOutputType::Console));

	ApplicationConfig application_config = m_Application->getConfig();

	WindowConfiguration config;
	config.set(WindowConfigurationOptions::RESIZABLE, true);
	m_Window.init(application_config.application_title, application_config.application_width, application_config.application_height, config);

	m_Renderer2D.init();
	m_Renderer3D.init();

	//TODO: pass the arguments into the app creation
	m_Application->onInit();
}

void hive::Engine::shutdown()
{
	TRACE_EVENT("engine", "Engine::shutdown");

	m_Application->onShutdown();

	m_Renderer3D.shutdown();
	m_Renderer2D.shutdown();


	Logger::shutdown();
}

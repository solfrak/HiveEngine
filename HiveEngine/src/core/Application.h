//
// Created by samuel on 11/17/24.
//
#pragma once
#include "hvpch.h"

namespace hive
{
	class Window;
	struct HAPI ApplicationConfig
	{
		int width, height;
		std::string title;
	};

	class HAPI Application
	{
	public:
		Application();
		~Application();

		void run();
		void tick();
		bool isRunning() const;
		void setConfig(const ApplicationConfig& config);

	private:
		bool terminated = false;
		ApplicationConfig m_config;
		Window* m_window;

	};

}


//Need to be implemented by the user
void application_init(hive::Application& app);
void application_tick(hive::Application& app);
void application_shutdown(hive::Application& app);


int main(int agrc, char ** argv)
{
	hive::Application app;
	app.run();
}
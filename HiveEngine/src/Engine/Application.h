//
// Created by samuel on 11/17/24.
//
#pragma once
#include "hvpch.h"

namespace hive
{
	class Engine;
}

namespace hive
{

	struct HAPI ApplicationConfig
	{
		const char* application_title;
		int application_width;
		int application_height;
	};

	class HAPI Application
	{
	public:
		virtual ~Application() = default;
		virtual ApplicationConfig getConfig() = 0;

		virtual void onInit() = 0;
		virtual void onUpdate() = 0;
		virtual void onRender() = 0;
		virtual void onShutdown() = 0;

	protected:
		friend Engine;
		bool m_Running = true;
	};
}

//This will be user defined
hive::Application* CreateApplication();


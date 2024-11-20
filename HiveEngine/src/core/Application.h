//
// Created by samuel on 11/17/24.
//
#pragma once
#include "hvpch.h"
#include "Rendering/Renderer3D.h"
#include "Rendering/Renderer2D.h"

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
		Application(void(*config)(Application&), void(*init)(Application&), void(*tick)(Application&), void(*shutdown)(Application&));
		~Application();

		void run();
		void tick();
		bool isRunning() const;
		void setConfig(const ApplicationConfig& config);

	public:
		Renderer2D m_renderer2D;
		Renderer3D m_renderer3D;

	private:
		bool terminated = false;
		ApplicationConfig m_config;
		Window* m_window;



	};

}


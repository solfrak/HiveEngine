#pragma once
#include <hvpch.h>
#include "Application.h"
#include "Window.h"
#include "Rendering/Renderer2D.h"
#include "Rendering/Renderer3D.h"

namespace hive
{
	class HAPI Engine
	{
	public:
		Engine(int argc, char** argv, Application* application);
		void run();

		static Window* get_window();
		static Application* get_application();
	private:
		void init();
		void shutdown();

		Window* m_Window;
		Application* m_Application;

		Renderer2D m_Renderer2D;
		Renderer3D m_Renderer3D;
	};

}

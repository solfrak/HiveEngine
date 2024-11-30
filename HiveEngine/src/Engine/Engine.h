#pragma once
#include <hvpch.h>
#include <Engine/Application.h>
#include <Engine/Window.h>
#include <Rendering/Renderer2D.h>
#include <Rendering/Renderer3D.h>

namespace hive
{
	class HAPI Engine
	{
	public:
		Engine(int argc, char** argv);
		void setApplication(Application *application);
		void init();
		void run();

		[[nodiscard]] static Window& get_window();
		[[nodiscard]] static Application* get_application();
	private:
		void shutdown();

	private:
		Window m_Window;
		Application* m_Application = nullptr;

		Renderer2D m_Renderer2D;
		Renderer3D m_Renderer3D;
	};

}

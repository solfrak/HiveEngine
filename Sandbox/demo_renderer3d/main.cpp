//
// Created by samuel on 11/14/24.
//
#include "Engine/Logger.h"
#include "Engine/LoggerFactory.h"
#include "Engine/Window.h"
#include "Engine/WindowConfiguration.h"

#include "Rendering/Renderer3D.h"
#include "Debug/Profiler.h"

int main()
{
	HPROFILE_BEGIN_SESSION();
	hive::Logger::init(hive::LoggerFactory::Create(hive::LogOutputType::Console));
	hive::WindowConfiguration config;
	config.set(hive::WindowConfigurationOptions::RESIZABLE, true);
	hive::Window* window = new hive::Window();
	window->init("HiveEngine", 800, 600, config);

	//WindowManager is a singleton that make it possible to access the Window across all the application
	hive::Renderer3D renderer_3d;
	renderer_3d.init();

	hive::Camera3D camera;
	camera.position = {20, 20, 20};
	camera.target = {0, 8, 0};
	camera.up = {0, 1.6, 0};

	hive::Mesh mesh("turret.obj", "turret_diffuse.png");
	mesh.rotation = {0, 0, 0};

	while (!window->shouldClose())
	{
		HPROFILE_SCOPE("Rendering");
		mesh.rotation.y += 0.5f;
		renderer_3d.beginScene(camera);
		// window->onUpdate();
		renderer_3d.drawMesh(mesh);
		renderer_3d.endScene();
	}

	renderer_3d.shutdown();

	HLOG_INFO("Application terminating");
	HPROFILE_END_SESSION();
}

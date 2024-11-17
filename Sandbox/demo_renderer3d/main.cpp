//
// Created by samuel on 11/14/24.
//
#include "core/Logging/Logger.h"
#include "core/Logging/LoggerFactory.h"
#include "core/Windowing/Window.h"
#include "core/Windowing/WindowFactory.h"
#include "core/Windowing/WindowManager.h"

#include "core/Rendering/Renderer3D.h"
#include "core/Debug/Profiler.h"

int main()
{
	HPROFILE_BEGIN_SESSION();
	hive::Logger::init(hive::LoggerFactory::createLogger(hive::LogOutputType::Console));
	hive::WindowConfiguration config;
	config.set(hive::WindowConfigurationOptions::RESIZABLE, true);
	hive::Window* window =  hive::WindowFactory::Create("HiveEngine", 800, 600, config);

	//WindowManager is a singleton that make it possible to access the Window across all the application
	hive::WindowManager::setCurrentWindow(std::shared_ptr<hive::Window>(window));
	hive::Renderer3D renderer_3d;
	renderer_3d.init();

	hive::Camera camera;
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

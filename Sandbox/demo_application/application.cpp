//
// Created by samuel on 11/17/24.
//
#include "core/Application.h"
#include "core/Logging/Logger.h"
#include "core/Memory/Memory.h"
#include "core/Rendering/Renderer3D.h"

hive::Renderer3D renderer_3d;
hive::Camera camera;
void application_init(hive::Application& app)
{
	hive::ApplicationConfig config { 800, 600, "MyAPP"};
	app.setConfig(config);
}

void application_tick(hive::Application& app)
{
	renderer_3d.beginScene(camera);
	renderer_3d.endScene();
}

void application_shutdown(hive::Application& app)
{
}

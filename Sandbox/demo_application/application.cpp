//
// Created by samuel on 11/17/24.
//
#include "core/Application.h"
#include "core/Logging/Logger.h"
#include "core/Rendering/Renderer3D.h"

hive::Renderer3D renderer_3d;
hive::Camera camera;
hive::Mesh *mesh;

void application_config(hive::Application& app)
{
	hive::ApplicationConfig config { 800, 600, "MyAPP"};
	app.setConfig(config);
}


void application_init(hive::Application& app)
{
	renderer_3d.init();
	camera.position = {20, 20, 20};
	camera.target = {0, 8, 0};
	camera.up = {0, 1.6, 0};

	mesh = new hive::Mesh("turret.obj", "turret_diffuse.png");
	mesh->rotation = {0, 0, 0};
}



void application_tick(hive::Application& app)
{
	mesh->rotation.y += 0.5f;
	renderer_3d.beginScene(camera);
	renderer_3d.drawMesh(*mesh);
	renderer_3d.endScene();
}

void application_shutdown(hive::Application& app)
{
	renderer_3d.shutdown();
}


int main(int agrc, char ** argv)
{
	hive::Application app(application_config, application_init, application_tick, application_shutdown);
	app.run();
}
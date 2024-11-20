//
// Created by samuel on 11/17/24.
//
#include <Engine/Application.h>
#include <Engine/Logger.h>
#include <Rendering/Renderer2D.h>
#include <Rendering/Renderer3D.h>


hive::Camera3D camera;
hive::Mesh *mesh;

void application_config(hive::Application& app)
{
	hive::ApplicationConfig config { 800, 600, "MyAPP"};
	app.setConfig(config);
}


void application_init(hive::Application& app)
{
	camera.position = {20, 20, 20};
	camera.target = {0, 8, 0};
	camera.up = {0, 1.6, 0};

	mesh = new hive::Mesh("turret.obj", "turret_diffuse.png");
	mesh->rotation = {0, 0, 0};
}



void application_tick(hive::Application& app)
{
	mesh->rotation.y += 0.5f;
	app.m_renderer3D.beginScene(camera);
	app.m_renderer3D.drawMesh(*mesh);
	app.m_renderer3D.endScene();

	app.m_renderer2D.beginScene();
	{
		app.m_renderer2D.drawFPS();
	}
	app.m_renderer2D.endScene();
}

void application_shutdown(hive::Application& app)
{
}


int main(int agrc, char ** argv)
{
	hive::Application app(application_config, application_init, application_tick, application_shutdown);
	app.run();
}
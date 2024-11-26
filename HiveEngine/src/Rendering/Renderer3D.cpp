//
// Created by samuel on 11/14/24.
//

#ifdef HIVE_RAYLIB_ENABLED
#include "Renderer3D.h"
#include "raylib.h"
#include "Mesh.h"
#include <Debug/Profiler.h>

static hive::Renderer3D *s_instance = nullptr;

void hive::Renderer3D::init()
{
	s_instance = this;
}

void hive::Renderer3D::shutdown()
{
	s_instance = nullptr;
}

void hive::Renderer3D::beginScene(Camera3D cam)
{
	HPROFILE_FUNCTION();
	ClearBackground(BLACK);
	::Camera temp_cam;
	temp_cam.position = {cam.position.x, cam.position.y, cam.position.z};
	temp_cam.target = {cam.target.x, cam.target.y, cam.target.z};
	temp_cam.up = {cam.up.x, cam.target.y, cam.target.z};
	temp_cam.fovy = 45;
	temp_cam.projection = CAMERA_PERSPECTIVE;

	BeginMode3D(temp_cam);
}

void hive::Renderer3D::endScene()
{
	EndMode3D();
}

void hive::Renderer3D::drawMesh(const hive::Mesh& mesh)
{
	HPROFILE_FUNCTION();
	mesh.draw();
}
#endif
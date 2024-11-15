//
// Created by samuel on 11/14/24.
//

#include "Renderer3D.h"
#include "raylib.h"
#include "Mesh.h"
#include "core/Profiling/profiler.h"

void hive::Renderer3D::init()
{
}

void hive::Renderer3D::shutdown()
{
}

void hive::Renderer3D::beginScene(Camera cam)
{
	HPROFILE_FUNCTION();
	BeginDrawing();
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
	EndDrawing();
}

void hive::Renderer3D::drawMesh(const hive::Mesh& mesh)
{
	HPROFILE_FUNCTION();
	mesh.draw();
}

//
// Created by samuel on 11/14/24.
//

#ifdef HIVE_RAYLIB_ENABLED
#include "Mesh.h"
#include <Debug/Profiler.h>

#include <raylib.h>
#include <raymath.h>


hive::Mesh::Mesh(const char* path, const char* texture)
{
	HPROFILE_TRACE_EVENT("engine", "Mesh::Mesh");
	Model model = LoadModel(path);
	Texture2D texture2d = LoadTexture(texture);

	m_model = new Model(model);
	m_model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture2d;
}

hive::Mesh::~Mesh()
{
	UnloadModel(*m_model);
}

void hive::Mesh::draw() const
{
	HPROFILE_TRACE_EVENT("engine", "Mesh::draw");
	Matrix final_matrix = MatrixRotateXYZ({DEG2RAD * rotation.x, DEG2RAD * rotation.y, DEG2RAD * rotation.z});
	m_model->transform = final_matrix;

	DrawModel(*m_model, {0, 0, 0}, 1, {255, 255, 255, 255});
}

#endif

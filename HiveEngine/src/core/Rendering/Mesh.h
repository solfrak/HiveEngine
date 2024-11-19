//
// Created by samuel on 11/14/24.
//

#pragma once
#include "hvpch.h"
#include "core/Math/MathType.h"
#ifdef HIVE_RAYLIB_ENABLED
struct Model;
namespace hive
{
	class HAPI Mesh
	{
	public:
		Mesh(const char* path, const char*  texture);
		~Mesh();
		void draw() const;

		Vec3 position;
		Vec3 rotation;
	private:
		Model* m_model;

	};
}
#endif

//
// Created by samuel on 11/14/24.
//

#pragma once
#include "hvpch.h"
#include <Core/Vector.h>
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

		Vec3f position;
		Vec3f rotation;
	private:
		Model* m_model;

	};
}
#endif

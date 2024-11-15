//
// Created by samuel on 11/14/24.
//

#pragma once
#include "hvpch.h"
#include "core/Math/MathType.h"
#ifdef HIVE_RAYLIB_ENABLED
#include <filesystem>
struct Model;
namespace hive
{
	class HAPI Mesh
	{
	public:
		Mesh(std::filesystem::path path, std::filesystem::path texture);
		~Mesh();
		void draw() const;

		Vec3 position;
		Vec3 rotation;
	private:
		Model* m_model;

	};
}
#endif

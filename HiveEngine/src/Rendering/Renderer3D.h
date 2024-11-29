//
// Created by samuel on 11/14/24.
//

#pragma once
#include "Camera3D.h"
#include "hvpch.h"
#include "Mesh.h"

namespace hive
{
	class HAPI Renderer3D
	{
	public:
		void init();
		void shutdown();

		static void beginScene(const Camera3D &cam);
		static void endScene();

		static void drawMesh(const Mesh& mesh);


	private:
	};
}




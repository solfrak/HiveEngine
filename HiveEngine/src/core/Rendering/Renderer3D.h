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

		//TODO: add Camera parameter
		void beginScene(Camera3D cam);
		void endScene();

		void drawMesh(const Mesh& mesh);


	private:
	};
}




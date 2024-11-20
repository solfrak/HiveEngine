//
// Created by samuel on 11/19/24.
//

#pragma once
#include "Camera2D.h"
#include "core/Math/MathType.h"

namespace hive
{
	class Renderer2D
	{
	public:
		void init();
		void shutdown();

		void beginScene();
		void endScene();

		void drawRectangle(Rectangle rect, Color4 color);
		void drawFPS();
		// void drawText();
	};
}





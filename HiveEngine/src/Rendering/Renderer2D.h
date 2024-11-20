//
// Created by samuel on 11/19/24.
//

#pragma once
#include <Core/Color.h>
#include <Core/Shape.h>

#include "Camera2D.h"

namespace hive
{
	class Renderer2D
	{
	public:
		void init();
		void shutdown();

		void beginScene();
		void endScene();

		void drawRectangle(hive::Rectangle rect, ColorRGBA color);
		void drawFPS();
		// void drawText();
	};
}





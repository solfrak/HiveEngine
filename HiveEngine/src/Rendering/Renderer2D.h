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

		static void beginScene();
		static void endScene();

		static void drawRectangle(hive::Rectangle rect, ColorRGBA color);
		static void drawFPS();
		static void drawText(const char* text, int font_size, Vec2i position, ColorRGBA color);
	};
}





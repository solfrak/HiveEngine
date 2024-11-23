#pragma once
#include <hvpch.h>
#include <Core/Color.h>
#include <Core/Shape.h>
#include "Texture.h"

#include "Camera2D.h"

namespace hive
{
	class HAPI Renderer2D
	{
	public:
		void init();
		void shutdown();

		static void beginScene();
		static void endScene();

		static void drawRectangle(hive::Rectangle rect, ColorRGBA color);
		static void drawTexture(hive::Texture texture, Rectangle rect, Vec2i position);
		static void drawFPS();
		static void drawText(const char* text, int font_size, Vec2i position, ColorRGBA color);
	};
}





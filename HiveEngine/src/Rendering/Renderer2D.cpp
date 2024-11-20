//
// Created by samuel on 11/19/24.
//
#include "raylib.h"
#ifdef HIVE_RAYLIB_ENABLED
#include "Renderer2D.h"

void hive::Renderer2D::init()
{
}

void hive::Renderer2D::shutdown()
{
}

void hive::Renderer2D::beginScene()
{
	// BeginDrawing();
}

void hive::Renderer2D::endScene()
{
	// EndDrawing();
}

void hive::Renderer2D::drawRectangle(Rectangle rect, ColorRGBA color)
{
	DrawRectangle(rect.position.x, rect.position.y, rect.size.w, rect.size.h, {color.r, color.g, color.b, color.a});
}

void hive::Renderer2D::drawFPS()
{
	DrawFPS(0, 0);
}
#endif

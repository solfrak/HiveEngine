//
// Created by samuel on 11/19/24.
//
#include "raylib.h"
#ifdef HIVE_RAYLIB_ENABLED
#include "Renderer2D.h"

static hive::Renderer2D* g_Renderer2D = nullptr;

void hive::Renderer2D::init()
{
	g_Renderer2D = this;
}

void hive::Renderer2D::shutdown()
{
	g_Renderer2D = nullptr;
}

void hive::Renderer2D::beginScene()
{

}

void hive::Renderer2D::endScene()
{

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

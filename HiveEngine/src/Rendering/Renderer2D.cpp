#ifdef HIVE_RAYLIB_ENABLED
#include "raylib.h"
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

void hive::Renderer2D::drawTexture(Texture texture, Rectangle rect, Vec2i position)
{
	::Texture raylib_texture = {texture.id, texture.width, texture.height, texture.mipmap, texture.format};
	DrawTextureRec(raylib_texture, {(float)rect.position.x, (float)rect.position.y, (float)rect.size.w, (float)rect.size.h}, {(float)position.x, (float)position.y},WHITE);
}

void hive::Renderer2D::drawFPS()
{
	DrawFPS(0, 0);
}

void hive::Renderer2D::drawText(const char* text, int font_size, Vec2i position, ColorRGBA color)
{
	DrawText(text, position.x, position.y, font_size, {color.r, color.g, color.b, color.a});
}
#endif

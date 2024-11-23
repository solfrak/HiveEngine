//
// Created by samuel on 11/22/24.
//

#include "RenderCommand.h"

#ifdef HIVE_RAYLIB_ENABLED
#include <raylib.h>

hive::ColorRGBA clear_color;
void hive::RenderCommand::ClearBuffer()
{
	ClearBackground({clear_color.r, clear_color.g, clear_color.b, clear_color.a});
}
void hive::RenderCommand::SetClearColor(ColorRGBA color)
{
	clear_color = color;
}
void hive::RenderCommand::BeginFrame()
{
	BeginDrawing();
}
void hive::RenderCommand::EndFrame()
{
	EndDrawing();
}

void hive::RenderCommand::BeginRenderTexture(RenderTexture render_texture)
{
	RenderTexture2D raylib_texture = {render_texture.id,
		{render_texture.color.id, render_texture.color.width, render_texture.color.height, render_texture.color.mipmap, render_texture.color.format},
		{render_texture.depth.id, render_texture.depth.width, render_texture.depth.height, render_texture.depth.mipmap, render_texture.depth.format}};

	BeginTextureMode(raylib_texture);
}

void hive::RenderCommand::EndRenderTexture()
{
	EndTextureMode();
}
#endif

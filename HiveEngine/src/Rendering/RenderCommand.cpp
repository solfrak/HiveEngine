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
#endif
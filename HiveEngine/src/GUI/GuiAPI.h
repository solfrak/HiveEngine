#pragma once

#include <hvpch.h>
#include <GUI/GuiType.h>
#include <GUI/GuiRenderCommand.h>
#include <Rendering/Texture.h>

namespace hive
{
	namespace gui
	{
		HAPI GuiContext *Initialize();

		void HAPI Shutdown(GuiContext *&ctx);

		void HAPI BeginFrame(GuiContext *ctx);

		void HAPI EndFrame(GuiContext *ctx);


		//Container
		HAPI void BeginWindow(GuiContext *ctx, const char *title, Rectangle bounds);
		HAPI void EndWindow(GuiContext *ctx);

		//Widget
		HAPI void Label(GuiContext *ctx, const char* label, Vec2i position);
		HAPI void Image(GuiContext* ctx, Texture* texture, Vec2i position, Vec2i size);

		//Utils
		HAPI GuiRenderCommand *GetRenderCommand(GuiContext *ctx, int &size);

	}
}
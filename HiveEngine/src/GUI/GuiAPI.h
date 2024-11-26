#pragma once

#include "hvpch.h"
#include "GuiType.h"
#include "GuiRenderCommand.h"

namespace hive
{
	namespace gui
	{
		HAPI GuiContext *Initialize();

		void HAPI Shutdown(GuiContext *&ctx);

		void HAPI BeginFrame(GuiContext *ctx);

		void HAPI EndFrame(GuiContext *ctx);

		HAPI void BeginWindow(GuiContext *ctx, const char *title, Rectangle bounds);

		HAPI void EndWindow(GuiContext *ctx);

		HAPI GuiRenderCommand *GetRenderCommand(GuiContext *ctx, int &size);

	}
}
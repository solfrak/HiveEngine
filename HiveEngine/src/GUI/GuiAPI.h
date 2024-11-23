#pragma once

#include "GuiContext.h"
#include "hvpch.h"

namespace hive::gui
{
	void HAPI Initialize(GuiContext *ctx);
	void HAPI Shutdown(GuiContext *ctx);

	void HAPI BeginFrame(GuiContext *ctx);
	void HAPI EndFrame(GuiContext *ctx);

	void HAPI BeginWindow(GuiContext *ctx);
	void HAPI EndWindow(GuiContext *ctx);

	//TODO return a RenderCommand array instead
	void* HAPI GetRenderCommand(GuiContext *ctx, int &size);
}
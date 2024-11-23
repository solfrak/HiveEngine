#include "GuiAPI.h"

#include "Ressource/Memory.h"

void hive::gui::Initialize(GuiContext* ctx)
{
	ctx = static_cast<GuiContext*>(hmalloc(sizeof(GuiContext)));
}

void hive::gui::Shutdown(GuiContext *ctx)
{
	hfree(sizeof(GuiContext), ctx);
}

void hive::gui::BeginFrame(GuiContext* ctx)
{
}

void hive::gui::EndFrame(GuiContext* ctx)
{
}

void hive::gui::BeginWindow(GuiContext* ctx)
{
}

void hive::gui::EndWindow(GuiContext* ctx)
{
}

// void* hive::gui::GetRenderCommand(GuiContext* ctx, int& size)
// {
// 	return nullptr;
// }

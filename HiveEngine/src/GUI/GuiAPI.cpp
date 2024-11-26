#include "GuiAPI.h"
#include "GuiRenderCommand.h"

#include "Ressource/Memory.h"

//Utils functions
size_t stringToHash(const std::string& str)
{
	constexpr std::hash<std::string> hashFunction;
	return hashFunction(str);
}

void pushRenderCommand(hive::gui::GuiContext* ctx, const hive::gui::GuiRenderCommand &command)
{
	ctx->renderCommand[ctx->renderCommandCount++] = command;
}



//=======================================

//API
hive::gui::GuiContext* hive::gui::Initialize()
{
	// return static_cast<GuiContext*>(hmalloc(sizeof(GuiContext)));
	return new GuiContext();
}


void hive::gui::Shutdown(GuiContext *&ctx)
{
	hfree(sizeof(GuiContext), ctx);
}

void hive::gui::BeginFrame(GuiContext* ctx)
{
	//Clear the render command buffer
	ctx->renderCommandCount = 0;
}

void hive::gui::EndFrame(GuiContext* ctx)
{

}

hive::gui::Container getContainer(hive::gui::GuiContext * ctx, size_t id)
{
	if(ctx->containerPool.find(id) != ctx->containerPool.end())
	{
		return ctx->containerPool.at(id);
	}

	constexpr hive::gui::Container new_container = {{0, 0, 0, 0}};
	ctx->containerPool[id] = new_container;
	return new_container;
}

void hive::gui::BeginWindow(GuiContext *ctx, const char *title, Rectangle bounds)
{
	auto container_id = stringToHash(title);
	Container container = getContainer(ctx, container_id);

	//First time initializing the container
	if(container.rect.size.w == 0)
	{
		container.rect = bounds;

		if(!ctx->containerStack.empty())
		{
			//Place the container relative to it's parent
			const auto parent = ctx->containerStack.top();
			container.rect.position.x += parent->rect.position.x;
			container.rect.position.y += parent->rect.position.y;
		}
	}

	ctx->containerStack.push(&ctx->containerPool[static_cast<int>(container_id)]);

	GuiRenderCommand border_command = {};
	border_command.type = GuiRenderCommandType::Rectangle;
	//TODO: Adjust color based on context style
	Rectangle border_rect = {
		{container.rect.position.x - 1, container.rect.position.y - 1},
		{container.rect.size.w + 2, container.rect.size.h + 2}
	};
	border_command.rect = {border_rect, {100, 100, 100, 255}};
	pushRenderCommand(ctx, border_command);

	GuiRenderCommand box_command = {};
	box_command.type = GuiRenderCommandType::Rectangle;
	//TODO: Adjust color based on context style
	box_command.rect = {container.rect, {25,25,25,255}};
	pushRenderCommand(ctx, box_command);

	GuiRenderCommand header_command = {};
	header_command.type = GuiRenderCommandType::Rectangle;
	//TODO: Adjust color based on context style
	Rectangle header_rect = {
		container.rect.position,
		{container.rect.size.w, 20}
	};
	header_command.rect = {header_rect, {50,50,50,255}};
	pushRenderCommand(ctx, header_command);
}



void hive::gui::EndWindow(GuiContext* ctx)
{
	ctx->containerStack.pop();
}

hive::gui::GuiRenderCommand * hive::gui::GetRenderCommand(GuiContext *ctx, int &size)
{
	size = ctx->renderCommandCount;
	return ctx->renderCommand;
}
#include <Engine/Entry.h>

#include "GUI/GuiAPI.h"
#include "GUI/GuiType.h"
#include "Rendering/RenderCommand.h"
#include "Rendering/RenderTexture.h"
const int TEXTURE_WIDTH = 100;
const int TEXTURE_HEIGHT = 100;

class DemoApp : public hive::Application
{
public:
	DemoApp(hive::Engine &engine);
	void onUpdate() override;
	void onInit() override;
	void onShutdown() override;
	hive::ApplicationConfig getConfig() override;
	~DemoApp() override = default;
	void onRender() override;
private:
	hive::RenderTexture m_renderTexture = {};
	hive::gui::GuiContext* ctx = nullptr;
};

DemoApp::DemoApp(hive::Engine &engine) : Application(engine)
{

}

//Game Logic Here
void DemoApp::onUpdate()
{
	if(hive::Engine::get_window().shouldClose())
	{
		m_Running = false;
	}

	hive::gui::BeginFrame(ctx);
	{
		hive::gui::BeginWindow(ctx, "Hello World", {99, 0, 255, 255});
		{

		}
		hive::gui::EndWindow(ctx);
	}

	hive::gui::EndFrame(ctx);
}

void DemoApp::onInit()
{
	hive::RenderCommand::SetClearColor({255, 0, 255, 255});
	m_renderTexture = hive::CreateRenderTexture(TEXTURE_WIDTH, TEXTURE_HEIGHT);
	ctx = hive::gui::Initialize();
}

void DemoApp::onShutdown()
{
	hive::gui::Shutdown(ctx);
}

hive::ApplicationConfig DemoApp::getConfig()
{
	return {"Demo Application", 800, 600};
}

//Render Logic Here
void DemoApp::onRender()
{
	//Render on a texture
	hive::RenderCommand::BeginRenderTexture(m_renderTexture);
	{
		hive::RenderCommand::SetClearColor({0, 0, 0, 255});
		hive::RenderCommand::ClearBuffer();
		hive::Renderer2D::beginScene();
		{
			hive::Renderer2D::drawFPS();
		}
		hive::Renderer2D::endScene();
	}
	hive::RenderCommand::EndRenderTexture();

	//Render the texture on the screen buffer
	hive::RenderCommand::SetClearColor({255, 0, 255, 255});
	hive::RenderCommand::ClearBuffer();
	hive::Renderer2D::drawTexture(m_renderTexture.color, {0, 0, TEXTURE_WIDTH, -TEXTURE_HEIGHT}, {0, 0});

	//Render UI
	int size;
	hive::gui::GuiRenderCommand* commands = hive::gui::GetRenderCommand(ctx, size);

	for(int i = 0; i < size; i++)
	{
		switch (commands[i].type)
		{
			case hive::gui::GuiRenderCommandType::Rectangle:
				hive::Renderer2D::drawRectangle(commands[i].rect.rect, commands[i].rect.color);
				break;
			case hive::gui::GuiRenderCommandType::Label:
				break;
		}
	}
}


hive::Application* CreateApplication(hive::Engine &engine)
{
	return new DemoApp(engine);
}

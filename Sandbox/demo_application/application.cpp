#include <Engine/Entry.h>
#include <Engine/Logger.h>

#include "GUI/GuiAPI.h"
#include "GUI/GuiType.h"
#include "Rendering/RenderCommand.h"
#include "Rendering/RenderTexture.h"


const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const int SCENE_WIDTH = SCREEN_WIDTH * 0.3f;
const int SCENE_HEIGHT = SCREEN_HEIGHT;

const int CONSOLE_WIDTH = SCREEN_WIDTH - SCENE_WIDTH;
const int CONSOLE_HEIGHT = SCREEN_HEIGHT * 0.3f;

const int TEXTURE_WIDTH = SCREEN_WIDTH - SCENE_WIDTH;
const int TEXTURE_HEIGHT = SCREEN_HEIGHT - CONSOLE_HEIGHT;
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
	hive::Camera3D cam = {};
	hive::Mesh *turret;
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
		hive::gui::BeginWindow(ctx, "Scene", {0, 0, SCENE_WIDTH, SCENE_HEIGHT});
		{

		}
		hive::gui::EndWindow(ctx);

		hive::gui::BeginWindow(ctx, "Console", {SCENE_WIDTH + 1, SCREEN_HEIGHT - CONSOLE_HEIGHT, CONSOLE_WIDTH, CONSOLE_HEIGHT});
		{

		}
		hive::gui::EndWindow(ctx);
	}

	hive::gui::EndFrame(ctx);

	turret->rotation.y += 0.5f;
}

void DemoApp::onInit()
{
	hive::RenderCommand::SetClearColor({255, 0, 255, 255});
	m_renderTexture = hive::CreateRenderTexture(TEXTURE_WIDTH, TEXTURE_HEIGHT);
	ctx = hive::gui::Initialize();

	turret = new hive::Mesh("turret.obj", "turret_diffuse.png");
	turret->rotation = {0, 0, 0};

	cam.position = {20, 20, 20};
	cam.target = {0, 8, 0};
	cam.up = {0, 1.6, 0};

}

void DemoApp::onShutdown()
{
	hive::gui::Shutdown(ctx);
}

hive::ApplicationConfig DemoApp::getConfig()
{
	return {"Demo Application", SCREEN_WIDTH, SCREEN_HEIGHT};
}

//Render Logic Here
void DemoApp::onRender()
{
	//Render on a texture
	hive::RenderCommand::BeginRenderTexture(m_renderTexture);
	{
		hive::RenderCommand::SetClearColor({0, 0, 0, 255});
		hive::RenderCommand::ClearBuffer();
		hive::Renderer3D::beginScene(cam);
		{
			hive::Renderer3D::drawMesh(*turret);
		}
		hive::Renderer3D::endScene();

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
				hive::Renderer2D::drawText(commands[i].label.text, commands[i].label.font_size, commands[i].label.position, commands[i].label.color);
				break;
		}
	}

	hive::Renderer2D::drawTexture(m_renderTexture.color, {0, 0, TEXTURE_WIDTH, -TEXTURE_HEIGHT}, {SCENE_WIDTH + 1, 0});
}


hive::Application* CreateApplication(hive::Engine &engine)
{
	return new DemoApp(engine);
}

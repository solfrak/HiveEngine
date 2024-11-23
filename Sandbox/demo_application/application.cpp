#include <Engine/Entry.h>
#include "Rendering/RenderCommand.h"
#include "Rendering/RenderTexture.h"

class DemoApp : public hive::Application
{
public:
	void onUpdate() override;
	void onInit() override;
	void onShutdown() override;
	hive::ApplicationConfig getConfig() override;
	~DemoApp() override = default;
	void onRender() override;
private:
	hive::RenderTexture m_renderTexture = {};
};

//Game Logic Here
void DemoApp::onUpdate()
{
	if(hive::Engine::get_window()->shouldClose())
	{
		m_Running = false;
	}

}

void DemoApp::onInit()
{
	hive::RenderCommand::SetClearColor({255, 0, 255, 255});
	m_renderTexture = hive::CreateRenderTexture(800, 600);
}

void DemoApp::onShutdown()
{
}

hive::ApplicationConfig DemoApp::getConfig()
{
	return {"Demo Application", 800, 600};
}


//Render Logic Here
void DemoApp::onRender()
{
	hive::RenderCommand::BeginRenderTexture(m_renderTexture);
	{
		hive::RenderCommand::ClearBuffer();
		hive::Renderer2D::beginScene();
		{
			hive::Renderer2D::drawFPS();
		}
		hive::Renderer2D::endScene();
	}
	hive::RenderCommand::EndRenderTexture();

	hive::Renderer2D::drawTexture(m_renderTexture.color, {0, 0, 800, -600}, {0, 0});
}


hive::Application* CreateApplication()
{
	//TODO: Should use a custom allocator
	return new DemoApp;
}

#include <Engine/Entry.h>

#include "../../HiveEngine/dep/raylib/src/raylib.h"

class DemoApp : public hive::Application
{
public:
	void onUpdate() override;
	void onInit() override;
	void onShutdown() override;
	hive::ApplicationConfig getConfig() override;
	~DemoApp() override = default;
	void onRender() override;
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
	hive::Renderer2D::beginScene();

	hive::Renderer2D::endScene();
}


hive::Application* CreateApplication()
{
	//TODO: Should use a custom allocator
	return new DemoApp;
}

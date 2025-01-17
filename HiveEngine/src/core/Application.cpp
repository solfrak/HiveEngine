#include "Application.h"
#include <rendering/Renderer.h>
#include <rendering/RendererFactory.h>

#include <chrono>
#include <stdexcept>

hive::Application::Application(ApplicationConfig &config) : memory_(), window_(config.window_config), renderer_(nullptr)
{
    config.render_config.window = &window_;
    if (!RendererFactory::createRenderer(config.render_config, &renderer_))
    {
        throw std::runtime_error("Failed to create renderer");
    }
}

hive::Application::~Application()
{
    RendererFactory::destroyRenderer(renderer_);
}



void hive::Application::run()
{
    on_init();

    while (!app_should_close_ && !window_.shouldClose())
    {
        window_.pollEvents();
        on_update(0);
    }

    on_destroy();
}

#include "Application.h"
#include <rendering/vulkan/GraphicsDeviceVulkan.h>

#include <chrono>
#include <stdexcept>

hive::Application::Application(const ApplicationConfig &config) : memory_(), window_(config.window_config), device_(nullptr)
{

    device_ = Memory::createObject<vk::GraphicsDevice_Vulkan, Memory::RENDERER>(window_);
}

hive::Application::~Application()
{
    Memory::destroyObject<vk::GraphicsDevice_Vulkan, Memory::RENDERER>(device_);
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

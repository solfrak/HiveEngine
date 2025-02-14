#include "Application.h"
#include <rendering/vulkan/GraphicsDeviceVulkan.h>


#include "Event/Event.h"
#include "Event/Service/BufferedEventService.h"

hive::Application::Application(const ApplicationConfig &config) : memory_(), event_service_{Memory::createObject<BufferEventService, Memory::ENGINE>()}, window_(config.window_config), device_vulkan_(nullptr)
{
    device_vulkan_ = Memory::createObject<vk::GraphicsDevice_Vulkan, Memory::RENDERER>(window_);
}

hive::Application::~Application()
{
    Memory::destroyObject<BufferEventService, Memory::ENGINE>(event_service_);
    Memory::destroyObject<vk::GraphicsDevice_Vulkan, Memory::RENDERER>(device_vulkan_);
}



void hive::Application::run()
{
    on_init();

    while (!app_should_close_ && !window_.shouldClose())
    {
        window_.pollEvents();
        input_.update();
        event_service_->FlushEvents();
        on_update(0);
    }

    on_destroy();
}

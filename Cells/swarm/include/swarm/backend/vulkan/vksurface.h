#pragma once
#include <swarm/swarm.h>
#include <vulkan/vulkan.h>
namespace swarm::vk
{
    bool CreateSurface(VkInstance instance, WindowHandle windowHandle, VkSurfaceKHR& surface);
    void DestroySurface(VkInstance instance, VkSurfaceKHR& surface);

    //Platform specific implementation
    bool CreateSurfacePlatform(VkInstance instance, WindowHandle windowHandle, VkSurfaceKHR& surface);
}
#include <swarm/precomp.h>
#include <swarm/backend/vulkan/vksurface.h>

namespace swarm::vk
{
    bool CreateSurface(VkInstance instance, WindowHandle windowHandle, VkSurfaceKHR&surface)
    {
        return CreateSurfacePlatform(instance, windowHandle, surface);
    }

    void DestroySurface(VkInstance instance, VkSurfaceKHR& surface)
    {
        vkDestroySurfaceKHR(instance, surface, nullptr);
        surface = nullptr;
    }
}

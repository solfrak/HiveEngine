#if defined(__linux__)
#include <hive/core/log.h>
#include <swarm/precomp.h>
#include <swarm/backend/vulkan/vksurface.h>

#include <vulkan/vulkan_wayland.h>
namespace swarm::vk
{
    bool CreateSurfaceWayland(VkInstance instance, WindowHandle windowHandle, VkSurfaceKHR& surface)
    {
        VkWaylandSurfaceCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
        createInfo.display = windowHandle.wayland.m_Display;
        createInfo.surface = windowHandle.wayland.m_Surface;

        if (vkCreateWaylandSurfaceKHR(instance, &createInfo, nullptr, &surface) != VK_SUCCESS)
        {
            hive::LogError(LogSwarm, "Failed to create surface");
            return false;
        }

        return true;
    }
}
#endif //__linux__
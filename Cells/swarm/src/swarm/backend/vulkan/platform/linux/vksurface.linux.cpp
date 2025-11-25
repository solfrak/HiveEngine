#if defined(__linux__)
#include <swarm/precomp.h>
#include <swarm/backend/vulkan/vksurface.h>

namespace swarm::vk
{
    extern bool CreateSurfaceWayland(VkInstance instance, WindowHandle windowHandle, VkSurfaceKHR& surface);
    extern bool CreateSurfaceX11(WindowHandle windowHandle, VkSurfaceKHR& surface);

    bool CreateSurfacePlatform(VkInstance instance, WindowHandle windowHandle, VkSurfaceKHR& surface)
    {
        switch (windowHandle.m_DisplayServer)
        {
            case DisplayServer::WAYLAND:
                return CreateSurfaceWayland(instance, windowHandle, surface);
            case DisplayServer::X11:
                return CreateSurfaceX11(windowHandle, surface);
            default:
                assert(false); //Should never end here
                return false;
        }
    }
}

#endif //__linux__
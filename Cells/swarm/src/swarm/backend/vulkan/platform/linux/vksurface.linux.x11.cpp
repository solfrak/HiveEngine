#if defined(__linux__)
#include <swarm/precomp.h>
#include <swarm/backend/vulkan/vksurface.h>
namespace swarm::vk
{
    bool CreateSurfaceX11(WindowHandle windowHandle, VkSurfaceKHR& surface)
    {
        return true;
    }
}
#endif //__linux__
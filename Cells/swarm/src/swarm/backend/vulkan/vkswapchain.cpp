#include "hive/core/log.h"
#include "swarm/swarm.h"
#include <swarm/precomp.h>
#include <swarm/backend/vulkan/vkswapchain.h>

#include <VkBootstrap.h>
namespace swarm::vk
{
    bool CreateSwapchain(vkb::Device const& device, VkSurfaceKHR surface, vkb::Swapchain& swapchain)
    {
        vkb::SwapchainBuilder swapchainBuilder{device, surface};
        swapchainBuilder.add_image_usage_flags(VK_IMAGE_USAGE_TRANSFER_DST_BIT);

        auto swapchainResult = swapchainBuilder.build();

        if(!swapchainResult.has_value())
        {
            hive::LogError(LogSwarm, "Failed to create swapchain");
            return false;
        }

        swapchain = swapchainResult.value();
        return true;
    }

    void DestroySwapchain(vkb::Swapchain const& swapchain)
    {
        vkb::destroy_swapchain(swapchain);
    }
}

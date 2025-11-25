#pragma once

#include <VkBootstrap.h>
namespace swarm::vk
{
    bool CreateSwapchain(vkb::Device const& device, VkSurfaceKHR surface, vkb::Swapchain& swapchain);
    void DestroySwapchain(vkb::Swapchain const& swapchain);
}

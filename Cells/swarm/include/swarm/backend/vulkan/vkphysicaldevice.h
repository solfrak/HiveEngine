#pragma once
#include <VkBootstrap.h>

namespace swarm::vk
{
    bool SelectPhysicalDevice(vkb::Instance const& instance, vkb::PhysicalDevice& physicalDevice, VkSurfaceKHR surface);
}

#pragma once
#include <VkBootstrap.h>
#include <vulkan/vulkan.h>
namespace swarm::vk
{
    bool CreateDevice(vkb::PhysicalDevice const& physicalDevice, vkb::Device& device);
    void DestroyDevice(vkb::Device& device);
}

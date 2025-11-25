#pragma once
#include <vulkan/vulkan.h>
#include <VkBootstrap.h>
namespace swarm::vk
{
    bool CreateInstance(vkb::Instance& instance);
    void DestroyInstance(vkb::Instance& instance);
}
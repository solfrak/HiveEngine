#pragma once

#include <vulkan/vulkan.h>
#include <VkBootstrap.h>
namespace swarm::vk
{
    struct GraphicBackendData
    {
        vkb::Instance m_Instance;
        vkb::PhysicalDevice m_PhysicalDevice;
        vkb::Device m_Device;
        vkb::Swapchain m_Swapchain;

        VkSurfaceKHR m_Surface{VK_NULL_HANDLE};
    };
}

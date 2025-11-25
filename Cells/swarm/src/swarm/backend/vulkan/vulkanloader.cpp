#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1
#include <vulkan/vulkan.hpp>

VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE


namespace swarm
{
    void initLoader()
    {
        VULKAN_HPP_DEFAULT_DISPATCHER.init();
    }

    void initLoaderInstance(VkInstance instance)
    {
        vk::Instance vkInstance{instance};
        VULKAN_HPP_DEFAULT_DISPATCHER.init(vkInstance);
    }

    void initLoaderDevice(VkDevice device)
    {
        vk::Device vkDevice{device};
        VULKAN_HPP_DEFAULT_DISPATCHER.init(vkDevice);
    }
}

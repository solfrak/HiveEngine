#include <rendering/RendererPlatform.h>
#ifdef HIVE_BACKEND_VULKAN_SUPPORTED
#include "vulkan_descriptor.h"
#include "vulkan_types.h"

#include <core/Memory.h>
#include <core/Logger.h>

namespace hive::vk
{
    void destroy_descriptor_pool(const VulkanDevice &device, VkDescriptorPool&descriptor_pool)
    {
        vkDestroyDescriptorPool(device.logical_device, descriptor_pool, nullptr);
    }

    void destroy_descriptor_set_layout(const VulkanDevice &device, VkDescriptorSetLayout&descriptor_set_layout)
    {
        vkDestroyDescriptorSetLayout(device.logical_device, descriptor_set_layout, nullptr);
    }

}
#endif

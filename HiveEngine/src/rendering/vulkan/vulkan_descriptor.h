#pragma once
#include <hvpch.h>
#include <unordered_map>
#include <vector>
// #include "vulkan_types.h"

#include <vulkan/vulkan.h>

namespace hive::vk
{
    struct VulkanDevice;
}

namespace hive::vk
{
    void destroy_descriptor_pool(const VulkanDevice &device, VkDescriptorPool &descriptor_pool);
    void destroy_descriptor_set_layout(const VulkanDevice &device, VkDescriptorSetLayout &descriptor_set_layout);
}

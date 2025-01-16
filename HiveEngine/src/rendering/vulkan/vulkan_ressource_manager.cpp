//
// Created by samuel on 15/01/25.
//

#include "vulkan_ressource_manager.h"
#include "vulkan_pipeline.h"

hive::vk::VulkanResourceManager::VulkanResourceManager() : shaders_(16)
{
}

hive::ShaderProgramHandle hive::vk::VulkanResourceManager::allocShader()
{
    return shaders_.getAvailableId();
}

hive::vk::VulkanPipeline & hive::vk::VulkanResourceManager::getPipeline(ShaderProgramHandle shader)
{
    return shaders_.getData(shader);
}

void hive::vk::VulkanResourceManager::destroyShader(ShaderProgramHandle shader)
{
    shader_to_destroy_.push_back(shader);
}

void hive::vk::VulkanResourceManager::processShaderDestroy(const VulkanDevice &device, const u32 current_frame, const bool force)
{
    std::vector<u32> item_destroyed;
    for (u32 i = 0; i < shader_to_destroy_.size(); i++)
    {
        auto &shader_data = getPipeline(shader_to_destroy_[i]);
        if (!force && shader_data.last_frame_used != current_frame) continue;

        destroy_graphics_pipeline(device, shader_data);
        shaders_.clearData(shader_to_destroy_[i]);
        item_destroyed.push_back(i);
    }
    for (auto i: item_destroyed)
    {
        shader_to_destroy_.erase(shader_to_destroy_.begin() + i);
    }
}

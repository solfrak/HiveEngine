#include <rendering/RendererPlatform.h>



#ifdef HIVE_BACKEND_VULKAN_SUPPORTED
#include "GraphicsDeviceVulkan.h"

#include <core/Memory.h>
#include <core/Logger.h>

#include "vulkan_init.h"
#include "vulkan_debug.h"
#include "vulkan_swapchain.h"
#include "vulkan_device.h"
#include "vulkan_renderpass.h"
#include "vulkan_command.h"
#include "vulkan_sync.h"
#include "vulkan_buffer.h"
#include "vulkan_shader.h"
#include "vulkan_pipeline.h"
#include "vulkan_descriptor.h"
#include "vulkan_image.h"

#include <array>

hive::vk::GraphicsDevice_Vulkan::GraphicsDevice_Vulkan(const Window &window)
{
    if (!create_instance(instance_, window)) return;
    if (config::enable_validation && !setup_debug_messenger(instance_, debugMessenger)) return;
    if (!create_surface(instance_, window, surface_khr_)) return;
    if (!create_device(instance_, surface_khr_, device_)) return;
    if (!create_swapchain(device_, surface_khr_, window, swapchain_)) return;
    if (!create_renderpass(device_, swapchain_, render_pass_)) return;
    if (!create_framebuffer(device_, swapchain_, render_pass_, framebuffer_)) return;
    if (!create_command_pool(device_)) return;
    if (!create_command_buffer(device_, command_buffers_, MAX_FRAME_IN_FLIGHT)) return;

    if (!create_semaphore(device_, sem_image_available_, MAX_FRAME_IN_FLIGHT)
        || !create_semaphore(device_, sem_render_finished_, MAX_FRAME_IN_FLIGHT)
        || !create_fence(device_, fence_in_flight_, MAX_FRAME_IN_FLIGHT, true))
        return;

    //Setup ressources
    for(i32 i = 0; i < 32; i++)
    {
        available_buffers.push(i);
        available_pipeline.push(i);
        available_image.push(i);
    }

    LOG_INFO("Device init succesfull");
    is_graphics_device_ready_ = true;
}

hive::vk::GraphicsDevice_Vulkan::~GraphicsDevice_Vulkan()
{
    WaitForGPU();

    destroy_swapchain(device_, swapchain_);
    destroy_renderpass(device_, render_pass_);
    destroy_framebuffer(device_, framebuffer_);
    destroy_semaphores(device_, sem_image_available_, MAX_FRAME_IN_FLIGHT);
    destroy_semaphores(device_, sem_render_finished_, MAX_FRAME_IN_FLIGHT);
    destroy_fences(device_, fence_in_flight_, MAX_FRAME_IN_FLIGHT);
    destroy_command_pool(device_);

    //debug messenger if in debug mode
    if(config::enable_validation)
    {
        destroy_debug_util_mesenger(instance_, debugMessenger);
    }

    destroy_surface(instance_, surface_khr_);
    destroy_device(device_);
    destroy_instance(instance_);
}



// bool hive::vk::GraphicsDevice_Vulkan::CreateShader(const ShaderDesc &desc, Shader &shader)
// {
//     VkShaderModule module;
//     if(!create_shader_module(device_, desc.path.c_str(), module))
//     {
//         return false;
//     }
//
//     shader.desc = desc;
//     shader.local_data = module;
//     return true;
// }
//
// void hive::vk::GraphicsDevice_Vulkan::DestroyShader(Shader &shader)
// {
//     auto module = static_cast<VkShaderModule>(shader.local_data);
//     destroy_shader_module(device_, module);
// }
//
// constexpr VkShaderStageFlagBits get_vulkan_stage(hive::ShaderStage stage)
// {
//     switch (stage)
//     {
//         case hive::ShaderStage::VERTEX:
//             return VK_SHADER_STAGE_VERTEX_BIT;
//         case hive::ShaderStage::FRAGMENT:
//             return VK_SHADER_STAGE_FRAGMENT_BIT;
//          default:
//             LOG_WARN("Vulkan: stage not supported");
//              return VK_SHADER_STAGE_VERTEX_BIT;
//     }
// }
bool hive::vk::GraphicsDevice_Vulkan::CreatePipeline(const PipelineDesc &desc, VulkanPipeline &pipeline) const
{

    std::vector<VkPipelineShaderStageCreateInfo> stages;
    for (auto stage: desc.shaders_stages)
    {
        switch (stage.stage)
        {
            case ShaderModule::ShaderStage::VERTEX:
                stages.push_back(create_stage_info(stage.module, StageType::VERTEX));
                break;
            case ShaderModule::ShaderStage::FRAGMENT:
                stages.push_back(create_stage_info(stage.module, StageType::FRAGMENT));
                break;
        }
    }

    VkPolygonMode cull_mode = VK_POLYGON_MODE_FILL;

    VulkanDescriptorPool::Builder pool_builder(device_);
    VulkanDescriptorSetLayout::Builder layout_builder(device_);

    pool_builder.setMaxtSets(MAX_FRAME_IN_FLIGHT);
    for (const auto layout: desc.layouts)
    {
        switch (layout.type)
        {
            case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
                pool_builder.addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, MAX_FRAME_IN_FLIGHT);
                layout_builder.addBinding(layout.binding_location, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                                          layout.stage, 1);
                break;
            case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
                pool_builder.addPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, MAX_FRAME_IN_FLIGHT);
                layout_builder.addBinding(layout.binding_location, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                                          layout.stage, 1);
                break;
            default: ;
        }
    }


    auto &pipeline_data = pipeline;
    pipeline_data.pool = pool_builder.build();
    pipeline_data.layout = layout_builder.build();

    pipeline_data.descriptor_sets.resize(MAX_FRAME_IN_FLIGHT);
    for (i32 i = 0; i < MAX_FRAME_IN_FLIGHT; i++)
    {
        if (!pipeline_data.pool->allocateDescriptor(pipeline_data.layout->getDescriptorSetLayout(),
                                                    pipeline_data.descriptor_sets[i])) return false;
    }

    if (!create_graphics_pipeline(device_, render_pass_, stages.data(), stages.size(), MAX_FRAME_IN_FLIGHT, cull_mode,
                                  pipeline_data))
    {
        return false;
    }

    return true;
}
//
// void hive::vk::GraphicsDevice_Vulkan::DestroyPipeline(Pipeline &pipeline)
// {
//     destroy_graphics_pipeline(device_, pipelines[pipeline.id]);
//     available_pipeline.push(pipeline.id);
// }
//
// void hive::vk::GraphicsDevice_Vulkan::PipelineUpdateDescriptor(const PipelineDescriptorSetDesc &desc,
//                                                                Pipeline &pipeline)
// {
//     for(i32 i = 0; i < MAX_FRAME_IN_FLIGHT; i++)
//     {
//         switch (desc.type)
//         {
//             case DescriptorType::UNIFORM_BUFFER:
//             {
//                 VkDescriptorBufferInfo info{};
//                 info.buffer = buffers[desc.buffer[0].id].vk_buffer; //We have only one ubo no matter how many frame in flight we have
//                 info.offset = 0;
//                 info.range = desc.buffer[0].desc.size;
//
//                 VkWriteDescriptorSet descriptorWrite{};
//                 descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//                 descriptorWrite.dstSet = pipelines[pipeline.id].descriptor_sets[i];
//                 descriptorWrite.dstBinding = desc.binding_location;
//                 descriptorWrite.dstArrayElement = 0;
//                 descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//                 descriptorWrite.descriptorCount = 1;
//                 descriptorWrite.pBufferInfo = &info;
//                 descriptorWrite.pImageInfo = nullptr; // Optional
//                 descriptorWrite.pTexelBufferView = nullptr; // Optional
//
//                 vkUpdateDescriptorSets(device_.logical_device, 1, &descriptorWrite, 0, nullptr);
//                 break;
//             }
//             case DescriptorType::SAMPLER2D:
//             {
//                 VkDescriptorImageInfo info{};
//                 info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
//                 info.imageView = images[desc.textures[0].id].vk_image_view; //We have only 1 image view and sampler no matter how many frame in flight we have
//                 info.sampler = images[desc.textures[0].id].vk_sampler;
//
//
//
//                 VkWriteDescriptorSet descriptorWrite{};
//                 descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//                 descriptorWrite.dstSet = pipelines[pipeline.id].descriptor_sets[i];
//                 descriptorWrite.dstBinding = desc.binding_location;
//                 descriptorWrite.dstArrayElement = 0;
//                 descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
//                 descriptorWrite.descriptorCount = 1;
//                 descriptorWrite.pBufferInfo = nullptr;
//                 descriptorWrite.pImageInfo = &info; // Optional
//                 descriptorWrite.pTexelBufferView = nullptr; // Optional
//
//                 vkUpdateDescriptorSets(device_.logical_device, 1, &descriptorWrite, 0, nullptr);
//                 break;
//             }
//         }
//     }
// }
//
//
// bool hive::vk::GraphicsDevice_Vulkan::CreateBuffer(const BufferDesc &desc, Buffer &buffer)
// {
//     VkBufferUsageFlags usage_flags{};
//     VkMemoryPropertyFlags memory_property_flags = 0;
//
//     //Usage flag
//     if(desc.usage_flag & BufferDesc::UsageFlag::INDEX_BUFFER)
//         usage_flags |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
//     if(desc.usage_flag & BufferDesc::UsageFlag::VERTEX_BUFFER)
//         usage_flags |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
//     if(desc.usage_flag & BufferDesc::UsageFlag::TRANSFER_DST)
//         usage_flags |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;
//     if(desc.usage_flag & BufferDesc::UsageFlag::TRANSFER_SRC)
//         usage_flags |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
//     if(desc.usage_flag & BufferDesc::UsageFlag::UNIFORM_BUFFER)
//         usage_flags |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
//
//     //Memory property
//     if(desc.mem_prop_flags & BufferDesc::MemoryType::DEVICE_LOCAL)
//         memory_property_flags |= VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
//     if(desc.mem_prop_flags & BufferDesc::MemoryType::HOST_COHERENT)
//         memory_property_flags |= VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
//     if(desc.mem_prop_flags & BufferDesc::MemoryType::HOST_VISIBLE)
//         memory_property_flags |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
//
//
//     if(available_buffers.empty())
//     {
//         LOG_ERROR("Vulkan device: no buffer is available at the moment");
//         return false;
//     }
//
//
//     const u32 id = available_buffers.front();
//     available_buffers.pop();
//     if(!create_buffer(device_, usage_flags, memory_property_flags, desc.size, buffers[id]))
//     {
//         LOG_ERROR("Vulkan device: failed to create the buffer");
//         return false;
//     }
//
//     buffer.desc = desc;
//     buffer.id = id;
//
//     return true;
// }
//
// void hive::vk::GraphicsDevice_Vulkan::FillBuffer(Buffer &buffer, void *data, const u32 size)
// {
//     buffer_fill_data(device_, buffers[buffer.id], data, size);
// }
//
// void hive::vk::GraphicsDevice_Vulkan::CopyBuffer(Buffer &src, Buffer &dest)
// {
//     buffer_copy(device_, buffers[src.id], buffers[dest.id], src.desc.size);
// }
//
// void hive::vk::GraphicsDevice_Vulkan::DestroyBuffer(Buffer &buffer)
// {
//     destroy_buffer(device_, buffers[buffer.id]);
//     available_buffers.push(buffer.id);
// }
//
// void hive::vk::GraphicsDevice_Vulkan::BufferUpdateData(Buffer &buffer, void *data)
// {
//     auto &[vk_buffer, vk_buffer_memory, map] = buffers[buffer.id];
//     memcpy(map, data, buffer.desc.size);
// }
//
// bool hive::vk::GraphicsDevice_Vulkan::CreateTexture(const TextureDesc &desc, const Buffer &buffer, Texture &texture)
// {
//     if(available_image.empty()) return false;
//
//     const u32 id = available_image.front();
//     available_image.pop();
//
//     VkFormat format = {};
//
//     switch (desc.format)
//     {
//         case TextureDesc::Format::R8G8B8A8_SRGB:
//             format = VK_FORMAT_R8G8B8A8_SRGB;
//             break;
//     }
//     create_image(device_, desc.width, desc.heigth, format, VK_IMAGE_TILING_OPTIMAL,
//                  VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
//                  images[id]);
//
//     transition_image_layout(device_, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED,
//                             VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, images[id]);
//     copy_buffer_to_image(device_, buffers[buffer.id], images[id], desc.width, desc.heigth);
//     transition_image_layout(device_, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
//                             VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, images[id]);
//
//
//     //TODO: maybe put this elsewhere
//     create_image_view(device_, images[id].vk_image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT,
//                       images[id].vk_image_view);
//     create_image_sampler(device_, images[id].vk_sampler);
//
//     texture.desc = desc;
//     texture.id = id;
//     return true;
// }
//
//
bool hive::vk::GraphicsDevice_Vulkan::BeginCmd()
{
    vkWaitForFences(device_.logical_device, 1, &fence_in_flight_[current_frame_], VK_TRUE, UINT64_MAX);
    vkResetFences(device_.logical_device, 1, &fence_in_flight_[current_frame_]);

    // processDestroyItems();
    vkAcquireNextImageKHR(device_.logical_device, swapchain_.vk_swapchain, UINT64_MAX, sem_image_available_[current_frame_], VK_NULL_HANDLE, &image_index_);

    vkResetCommandBuffer(command_buffers_[current_frame_], /*VkCommandBufferResetFlagBits*/ 0);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(command_buffers_[current_frame_], &beginInfo) != VK_SUCCESS) {
        LOG_ERROR("Vulkan: failed to begin recording command buffer!");
        return false;
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = render_pass_;
    renderPassInfo.framebuffer = framebuffer_.framebuffers[image_index_];
    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = swapchain_.extent_2d;

    std::array<VkClearValue, 2> clear_values{};
    clear_values[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
    clear_values[1].depthStencil = {1.0f, 0};

    renderPassInfo.clearValueCount = static_cast<u32>(clear_values.size());
    renderPassInfo.pClearValues = clear_values.data();


    vkCmdBeginRenderPass(command_buffers_[current_frame_], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    return true;
}
//
bool hive::vk::GraphicsDevice_Vulkan::EndCmd() const
{
    vkCmdEndRenderPass(command_buffers_[current_frame_]);

    if (vkEndCommandBuffer(command_buffers_[current_frame_]) != VK_SUCCESS)
    {
        LOG_ERROR("Vulkan: failed to record command buffer!");
        return false;
    }
    return true;
}
//
// void hive::vk::GraphicsDevice_Vulkan::CmdBindPipeline(Pipeline &pipeline)
// {
//     auto& data = pipelines[pipeline.id];
//     vkCmdBindPipeline(command_buffers_[current_frame_], VK_PIPELINE_BIND_POINT_GRAPHICS, data.vk_pipeline);
//     vkCmdBindDescriptorSets(command_buffers_[current_frame_], VK_PIPELINE_BIND_POINT_GRAPHICS, data.pipeline_layout, 0, 1, &data.descriptor_sets[current_frame_], 0, nullptr);
//
//     pipelines[pipeline.id].last_frame_used = current_frame_;
// }
//
// void hive::vk::GraphicsDevice_Vulkan::CmdDrawIndexed(const Buffer vertex_buffer, const Buffer index_buffer, const u32 nbr_indices)
// {
//
//     //TODO: remove viewport cmd
//     VkViewport viewport{};
//     viewport.x = 0.0f;
//     viewport.y = 0.0f;
//     viewport.width = (float) swapchain_.extent_2d.width;
//     viewport.height = (float) swapchain_.extent_2d.height;
//     viewport.minDepth = 0.0f;
//     viewport.maxDepth = 1.0f;
//     vkCmdSetViewport(command_buffers_[current_frame_], 0, 1, &viewport);
//
//
//     //TODO: remove scissor cmd
//     VkRect2D scissor{};
//     scissor.offset = {0, 0};
//     scissor.extent = swapchain_.extent_2d;
//     vkCmdSetScissor(command_buffers_[current_frame_], 0, 1, &scissor);
//
//
//     VkDeviceSize offsets[] = {0};
//     vkCmdBindVertexBuffers(command_buffers_[current_frame_], 0, 1, &buffers[vertex_buffer.id].vk_buffer, offsets);
//     vkCmdBindIndexBuffer(command_buffers_[current_frame_], buffers[index_buffer.id].vk_buffer, 0, VK_INDEX_TYPE_UINT32);
//
//     vkCmdDrawIndexed(command_buffers_[current_frame_], nbr_indices, 1, 0, 0, 0);
// }
//
bool hive::vk::GraphicsDevice_Vulkan::SubmitFrame()
{
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {sem_image_available_[current_frame_]};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &command_buffers_[current_frame_];

    VkSemaphore signalSemaphores[] = {sem_render_finished_[current_frame_]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(device_.graphics_queue, 1, &submitInfo, fence_in_flight_[current_frame_]) != VK_SUCCESS)
    {
        LOG_ERROR("Vulkan: failed to submit draw command buffer!");
        return false;
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {swapchain_.vk_swapchain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &image_index_;

    vkQueuePresentKHR(device_.present_queue, &presentInfo);

    current_frame_ = (current_frame_ + 1) % MAX_FRAME_IN_FLIGHT;


    return true;
}

void hive::vk::GraphicsDevice_Vulkan::WaitForGPU() const
{
    vkDeviceWaitIdle(device_.logical_device);
}

// void hive::vk::GraphicsDevice_Vulkan::DestroyTexture(hive::Texture &texture)
// {
//     destroy_image(device_, images[texture.id]);
// }

#endif

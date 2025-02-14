#include <core/Event/Event.h>
#include <core/Event/Service/IEventService.h>
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

hive::vk::GraphicsDevice_Vulkan::GraphicsDevice_Vulkan(const Window &window) : window_(window)
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

    IEventService::get_singleton()->Subscribe(EventCategory::Rendering, [this](const Event& event)
    {
        handle_rendering_event(event);
    });


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


void hive::vk::GraphicsDevice_Vulkan::recreate_swap_chain()
{
    vkDeviceWaitIdle(device_.logical_device);

    //Destroy old swapchain
    destroy_swapchain(device_, swapchain_);
    destroy_framebuffer(device_, framebuffer_);


    if (!create_swapchain(device_, surface_khr_, window_, swapchain_)) return;
    if (!create_framebuffer(device_, swapchain_, render_pass_, framebuffer_)) return;
}

void hive::vk::GraphicsDevice_Vulkan::handle_rendering_event(const Event &event)
{
    switch (event.type)
    {
        case EventType::FramebufferResized:
            recreate_swap_chain();
            break;
        default:
            LOG_DEBUG("Event of category Rendering is not supported on GraphicsDeviceVulkan");
            break;
    }
}

i32 hive::vk::GraphicsDevice_Vulkan::get_framebuffer_x() const
{
    return swapchain_.extent_2d.width;
}

i32 hive::vk::GraphicsDevice_Vulkan::get_framebuffer_y() const
{
    return swapchain_.extent_2d.height;
}


bool hive::vk::GraphicsDevice_Vulkan::BeginCmd()
{
    vkWaitForFences(device_.logical_device, 1, &fence_in_flight_[current_frame_], VK_TRUE, UINT64_MAX);

    // processDestroyItems();
    VkResult result = vkAcquireNextImageKHR(device_.logical_device, swapchain_.vk_swapchain, UINT64_MAX, sem_image_available_[current_frame_], VK_NULL_HANDLE, &image_index_);

    vkResetFences(device_.logical_device, 1, &fence_in_flight_[current_frame_]);
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


#endif

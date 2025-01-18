#pragma once
#include <core/Window.h>
#include <rendering/GraphicsDevice.h>
#include <rendering/vulkan/vulkan_types.h>
#include <vulkan/vulkan.h>
#include <queue>

namespace hive::vk
{
    class GraphicsDevice_Vulkan final : public GraphicsDevice
    {
    public:
        explicit GraphicsDevice_Vulkan(const Window& window);
        ~GraphicsDevice_Vulkan() override;

        // [[nodiscard]] bool
        // CreateSwapchain(const ::hive::SwapchainDesc &desc, ::hive::Swapchain swapchain) const override;
        [[nodiscard]] bool CreateShader(const ShaderDesc &desc, Shader &shader) override;

        void DestroyShader(Shader &shader) override;

        [[nodiscard]] bool CreatePipeline(const PipelineDesc &desc, Pipeline &pipeline) override;

        void DestroyPipeline(Pipeline &pipeline) override;

        void PipelineUpdateDescriptor(const PipelineDescriptorSetDesc &desc, Pipeline &pipeline) override;

        [[nodiscard]] bool CreateBuffer(const BufferDesc &desc, Buffer &buffer) override;

        void FillBuffer(Buffer &buffer, void *data, u32 size) override;

        void CopyBuffer(Buffer &src, Buffer &dest) override;

        void DestroyBuffer(Buffer &buffer) override;

        void BufferUpdateData(Buffer &buffer, void *data) override;

        [[nodiscard]] bool CreateTexture(const TextureDesc &desc, const Buffer &buffer, Texture &texture) override;

        void DestroyTexture(::hive::Texture &texture) override;


        [[nodiscard]] bool BeginCmd() override;

        [[nodiscard]] bool EndCmd() const override;

        void CmdBindPipeline(Pipeline &pipeline) override;
        void CmdDrawIndexed(Buffer vertex_buffer, Buffer index_buffer, u32 nbr_indices) override;

        bool SubmitFrame() override;

        void WaitForGPU() const override;


    protected:
        u32 current_frame_ = 0;
        u32 image_index_ = 0;

        VkInstance instance_ = VK_NULL_HANDLE;
        VkSurfaceKHR surface_khr_ = VK_NULL_HANDLE;
        VkDebugUtilsMessengerEXT debugMessenger{};

        VulkanDevice device_{};
        VulkanSwapchain swapchain_{};
        VkRenderPass render_pass_ = VK_NULL_HANDLE;
        VulkanFramebuffer framebuffer_{};

        static constexpr u32 MAX_FRAME_IN_FLIGHT = 3;
        VkCommandBuffer command_buffers_[MAX_FRAME_IN_FLIGHT] = {VK_NULL_HANDLE};

        VkSemaphore sem_image_available_[MAX_FRAME_IN_FLIGHT] = {VK_NULL_HANDLE};
        VkSemaphore sem_render_finished_[MAX_FRAME_IN_FLIGHT] = {VK_NULL_HANDLE};
        VkFence fence_in_flight_[MAX_FRAME_IN_FLIGHT] = {VK_NULL_HANDLE};

        //Resources

        //TODO: create a better resource a better way to handle multiple buffers instead of having a maximum
        VulkanBuffer buffers[32] = {};
        std::queue<u32> available_buffers {};

        VulkanPipeline pipelines[32] = {};
        std::queue<u32> available_pipeline {};

        VulkanImage images[32] = {};
        std::queue<u32> available_image {};


        bool is_graphics_device_ready_ = false;
    };

}



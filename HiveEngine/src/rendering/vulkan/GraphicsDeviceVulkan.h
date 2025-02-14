#pragma once
#include <core/Window.h>
#include <rendering/vulkan/vulkan_types.h>
#include <vulkan/vulkan.h>
#include <queue>

namespace hive::vk
{
    struct PipelineLayout
    {

        VkDescriptorType type;
        u32 binding_location;
        VkShaderStageFlags stage;
    };

    struct ShaderModule
    {
        VkShaderModule module;
        enum class ShaderStage
        {
            VERTEX, FRAGMENT
        } stage;
    };

    struct PipelineDesc
    {
        std::vector<ShaderModule> shaders_stages{};
        std::vector<PipelineLayout> layouts;
    };

    class GraphicsDevice_Vulkan
    {
    public:
        explicit GraphicsDevice_Vulkan(const Window& window);
        ~GraphicsDevice_Vulkan();

        VulkanDevice &getDevice() { return device_; }
        VkCommandBuffer &getCmdBuffer() { return command_buffers_[current_frame_]; }
        VulkanSwapchain &getSwapchain() { return swapchain_; }
        VkRenderPass &getRenderPass() { return render_pass_; }

        void recreate_swap_chain();

        void handle_rendering_event(const Event &event);


        [[nodiscard]] i32 get_framebuffer_x() const;
        [[nodiscard]] i32 get_framebuffer_y() const;


        [[nodiscard]] bool BeginCmd();

        [[nodiscard]] bool EndCmd() const;

        bool SubmitFrame();
        void WaitForGPU() const;


    protected:
        u32 current_frame_ = 0;
        u32 image_index_ = 0;

        const Window &window_;

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



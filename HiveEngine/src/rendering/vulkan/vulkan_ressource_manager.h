#pragma once
#include "vulkan_types.h"
#include <core/RessourceManager.h>
#include <rendering/RenderType.h>

namespace hive::vk
{
    class VulkanResourceManager
    {
    public:
        VulkanResourceManager();

        //Shaders
        ShaderProgramHandle allocShader();
        VulkanPipeline &getPipeline(ShaderProgramHandle shader);
        void destroyShader(ShaderProgramHandle shader);
        void processShaderDestroy(const VulkanDevice &device, u32 current_frame, bool force);

    private:
        RessourceManager<VulkanPipeline, ShaderProgramHandle> shaders_;
        std::vector<ShaderProgramHandle> shader_to_destroy_;
    };

}

#pragma once
#include "GraphicsType.h"

namespace hive
{
    class GraphicsDevice
    {
    public:
        virtual ~GraphicsDevice() = default;

        //Resource operation
        // [[nodiscard]] virtual bool CreateSwapchain(const SwapchainDesc &desc, Swapchain swapchain) const = 0;

        [[nodiscard]] virtual bool CreateShader(const ShaderDesc &desc, Shader &shader) = 0;
        virtual void DestroyShader(Shader &shader) = 0;

        [[nodiscard]] virtual bool CreateBuffer(const BufferDesc &desc, Buffer &buffer) = 0;
        virtual void FillBuffer(Buffer& buffer, void* data, u32 size) = 0;
        virtual void CopyBuffer(Buffer& src, Buffer& dest) = 0;
        virtual void BufferUpdateData(Buffer& buffer, void* data) = 0;
        virtual void DestroyBuffer(Buffer &buffer) = 0;

        [[nodiscard]] virtual bool CreatePipeline(const PipelineDesc &desc, Pipeline &pipeline) = 0;
        virtual void DestroyPipeline(Pipeline &pipeline) = 0;
        virtual void PipelineUpdateDescriptor(const PipelineDescriptorSetDesc &desc, Pipeline &pipeline) = 0;


        [[nodiscard]] virtual bool CreateTexture(const TextureDesc &desc, const Buffer &buffer, Texture &texture) = 0;
        virtual void DestroyTexture(Texture &texture) = 0;


        //Graphics operation
        [[nodiscard]] virtual bool BeginCmd() = 0;
        [[nodiscard]] virtual bool EndCmd() const = 0;

        virtual void CmdBindPipeline(Pipeline &pipeline) = 0;

        virtual void CmdDrawIndexed(Buffer vertex_buffer, Buffer index_buffer, u32 nbr_indices) = 0;

        virtual bool SubmitFrame() = 0;

        virtual void WaitForGPU() const = 0;


    };
}


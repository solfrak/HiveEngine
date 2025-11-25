#pragma once
#include <nvrhi/nvrhi.h>
#if defined(SWARM_VULKAN_ENABLED)
#include <swarm/backend/vulkan/graphicbackenddata.h>
namespace swarm { using GraphicBackendData = vk::GraphicBackendData; }
#else
#error "Unsupported backend"
#endif

#if defined(__linux__)
#include <swarm/platform/linux/platformhandle.h>
namespace swarm { using WindowHandle = WindowHandleLinux; }
#else
#error "Unsupported platform"
#endif

// #include <nvrhi/nvrhi.h>

namespace hive
{
    class LogCategory;
}
namespace swarm
{
    extern const hive::LogCategory LogSwarm;

    class GraphicDevice
    {
    public:
        GraphicDevice(WindowHandle windowHandle);
        ~GraphicDevice();

        void TestDraw();

        GraphicBackendData GetBackendData() const { return m_BackendData; }
        nvrhi::IDevice* GetDevice() const { return m_DeviceHandle.Get(); }
        std::vector<nvrhi::TextureHandle> GetSwapchainTextures() const { return m_SwapchainTextures; }

    private:
        GraphicBackendData m_BackendData{};
        VkFence m_AcquireFence;
        nvrhi::DeviceHandle m_DeviceHandle{nullptr};
        std::vector<nvrhi::TextureHandle> m_SwapchainTextures{nullptr};
        nvrhi::FramebufferHandle m_Framebuffer{nullptr};
    };
}

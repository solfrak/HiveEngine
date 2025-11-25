#include "nvrhi/common/resource.h"
#include "nvrhi/nvrhi.h"
#include "swarm/backend/vulkan/vkswapchain.h"
#include <swarm/precomp.h>
#include <swarm/swarm.h>

#include <swarm/backend/vulkan/vkinstance.h>
#include <swarm/backend/vulkan/vksurface.h>
#include <swarm/backend/vulkan/vkphysicaldevice.h>
#include <swarm/backend/vulkan/vkdevice.h>

#include <nvrhi/vulkan.h>
#include <nvrhi/utils.h>
#include <vulkan/vulkan_core.h>

namespace swarm
{
    extern void initLoader();

    extern void initLoaderInstance(VkInstance);

    extern void initLoaderDevice(VkDevice);

    GraphicDevice::GraphicDevice(WindowHandle windowHandle)
    {
        if (!vk::CreateInstance(m_BackendData.m_Instance)) return;
        if (!vk::CreateSurface(m_BackendData.m_Instance, windowHandle, m_BackendData.m_Surface)) return;
        if (!vk::SelectPhysicalDevice(m_BackendData.m_Instance, m_BackendData.m_PhysicalDevice,
                                      m_BackendData.m_Surface))
            return;
        if (!vk::CreateDevice(m_BackendData.m_PhysicalDevice, m_BackendData.m_Device)) return;
        if (!vk::CreateSwapchain(m_BackendData.m_Device, m_BackendData.m_Surface, m_BackendData.m_Swapchain)) return;

        //For nvrhi since they use Vulkan-Hpp
        initLoader();
        initLoaderInstance(m_BackendData.m_Instance);
        initLoaderDevice(m_BackendData.m_Device);

        nvrhi::vulkan::DeviceDesc description;
        description.instance = m_BackendData.m_Instance;
        description.physicalDevice = m_BackendData.m_PhysicalDevice;
        description.device = m_BackendData.m_Device;
        description.graphicsQueue = m_BackendData.m_Device.get_queue(vkb::QueueType::graphics).value();
        description.graphicsQueueIndex = m_BackendData.m_Device.get_queue_index(vkb::QueueType::graphics).value();

        //TODO: Hack for now
        std::vector<const char *> deviceExtension{
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };
        description.deviceExtensions = deviceExtension.data();
        description.numDeviceExtensions = deviceExtension.size();

        m_DeviceHandle = nvrhi::vulkan::createDevice(description);

        auto textureDesc = nvrhi::TextureDesc()
                .setDimension(nvrhi::TextureDimension::Texture2D)
                .setFormat(nvrhi::Format::SBGRA8_UNORM)
                .setWidth(m_BackendData.m_Swapchain.extent.width)
                .setHeight(m_BackendData.m_Swapchain.extent.height)
                .setIsRenderTarget(true)
                .setInitialState(nvrhi::ResourceStates::Present)
                .setKeepInitialState(true)
                .setDebugName("Swap Chain Image");

        auto nativeTextureOrImage = m_BackendData.m_Swapchain.get_images().value();
        m_SwapchainTextures.resize(nativeTextureOrImage.size());

        int i = 0;
        for (auto image: nativeTextureOrImage)
        {
            m_SwapchainTextures[i++] = m_DeviceHandle->createHandleForNativeTexture(
                nvrhi::ObjectTypes::VK_Image, image, textureDesc);
        }

        auto framebufferDesc = nvrhi::FramebufferDesc()
                .addColorAttachment(m_SwapchainTextures[0]); // you can specify a particular subresource if necessary

        m_Framebuffer = m_DeviceHandle->createFramebuffer(framebufferDesc);

        // Initialize in constructor after device creation:
        VkFenceCreateInfo fenceInfo = {};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT; // Start signaled so first wait succeeds
        vkCreateFence(m_BackendData.m_Device, &fenceInfo, nullptr, &m_AcquireFence);
    }

    GraphicDevice::~GraphicDevice()
    {
        m_DeviceHandle.Reset();

        vk::DestroySwapchain(m_BackendData.m_Swapchain);
        vk::DestroySurface(m_BackendData.m_Instance, m_BackendData.m_Surface);
        vk::DestroyDevice(m_BackendData.m_Device);
        vk::DestroyInstance(m_BackendData.m_Instance);
    }

    void GraphicDevice::TestDraw()
    {
        // Wait for previous frame
        vkWaitForFences(m_BackendData.m_Device, 1, &m_AcquireFence, VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(
            m_BackendData.m_Device,
            m_BackendData.m_Swapchain,
            UINT64_MAX,
            VK_NULL_HANDLE, // No semaphore
            m_AcquireFence, // Use fence instead
            &imageIndex
        );

        vkResetFences(m_BackendData.m_Device, 1, &m_AcquireFence);

        auto commandlist = m_DeviceHandle->createCommandList();

        commandlist->open();

        nvrhi::utils::ClearColorAttachment(commandlist, m_Framebuffer, 0, {1, 0, 0, 1});

        commandlist->close();

        m_DeviceHandle->executeCommandList(commandlist);
        m_DeviceHandle->waitForIdle();


        VkPresentInfoKHR presentInfo = {};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.swapchainCount = 1;
        VkSwapchainKHR swapchain = m_BackendData.m_Swapchain;
        presentInfo.pSwapchains = &swapchain;
        presentInfo.pImageIndices = &imageIndex;
        presentInfo.waitSemaphoreCount = 1;

        VkQueue presentQueue = m_BackendData.m_Device.get_queue(vkb::QueueType::graphics).value();
        vkQueuePresentKHR(presentQueue, &presentInfo);
    }
}

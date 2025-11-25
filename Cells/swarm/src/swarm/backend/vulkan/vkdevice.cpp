#include <swarm/precomp.h>
#include <swarm/backend/vulkan/vkdevice.h>

#include <swarm/swarm.h>
#include <hive/core/log.h>


namespace swarm::vk
{
    bool CreateDevice(vkb::PhysicalDevice const& physicalDevice, vkb::Device &device)
    {
        vkb::DeviceBuilder deviceBuilder{physicalDevice};

        auto deviceResult = deviceBuilder.build();
        if (!deviceResult.has_value())
        {
            hive::LogError(LogSwarm, "Failed to create device");
            return false;
        }

        device = deviceResult.value();
        return true;
    }

    void DestroyDevice(vkb::Device &device)
    {
        vkb::destroy_device(device);
    }
}

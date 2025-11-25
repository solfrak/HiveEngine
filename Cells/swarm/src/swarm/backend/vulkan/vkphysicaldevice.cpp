#include <hive/core/log.h>
#include <swarm/precomp.h>
#include <swarm/swarm.h>
#include <swarm/backend/vulkan/vkphysicaldevice.h>

namespace swarm::vk
{
    bool SelectPhysicalDevice(const vkb::Instance &instance, vkb::PhysicalDevice &physicalDevice, VkSurfaceKHR surface)
    {
        vkb::PhysicalDeviceSelector selector{instance, surface};
        selector.add_required_extension(VK_KHR_TIMELINE_SEMAPHORE_EXTENSION_NAME);

        VkPhysicalDeviceTimelineSemaphoreFeatures timelineFeatures{};
        timelineFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES;
        timelineFeatures.timelineSemaphore = VK_TRUE;
        selector.add_required_extension_features(timelineFeatures);

        auto physicalDeviceResult = selector.select();
        if (!physicalDeviceResult.has_value())
        {
            hive::LogError(LogSwarm, "Failed to select a suitable device");
            return false;
        }

        physicalDevice = physicalDeviceResult.value();
        return true;
    }
}

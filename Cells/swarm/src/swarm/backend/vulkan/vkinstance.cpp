#include <swarm/precomp.h>
#include <swarm/backend/vulkan/vkinstance.h>

#include <swarm/swarm.h>
#include <hive/core/log.h>

#include <VkBootstrap.h>

namespace swarm::vk
{
    bool CreateInstance(vkb::Instance& instance)
    {
        vkb::InstanceBuilder builder;
        builder.request_validation_layers();
        builder.use_default_debug_messenger();

        auto instanceResult = builder.build();
        if (!instanceResult.has_value())
        {
            hive::LogError(LogSwarm, "Failed to create instance!");
            return false;
        }

        instance = instanceResult.value();
        return true;
    }

    void DestroyInstance(vkb::Instance &instance)
    {
        vkb::destroy_instance(instance);
    }
}

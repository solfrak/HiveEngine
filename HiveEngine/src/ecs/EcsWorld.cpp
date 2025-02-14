#include "EcsWorld.h"
#include <core/Memory.h>

#include "entt/entt.hpp"
namespace hive
{
    class World::PImpl
    {
    public:
        entt::registry registry;
    };


    template<typename T>
    void World::add_component(int id, T data)
    {
        impl_->registry.emplace<T>(static_cast<entt::entity>(id), data);
    }

    template<typename T>
    T &World::get_component(int id)
    {
        return impl_->registry.get<T>(static_cast<entt::entity>(id));
    }

    World::World() : impl_(hive::Memory::createObject<PImpl, hive::Memory::ENGINE>())
    {
    }

    World::~World()
    {
        hive::Memory::destroyObject<PImpl, hive::Memory::ENGINE>(impl_);
    }

    int World::create() const
    {
        return static_cast<int>(impl_->registry.create());
    }
}
#include "Component_Registry.h"

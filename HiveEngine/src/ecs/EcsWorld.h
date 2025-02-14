#pragma once

namespace hive
{
class World
{
public:
    World();

    ~World();

    int create() const;

    template<typename T>
    void add_component(int id, T data);

    template<typename T>
    T &get_component(int id);

private:
    class PImpl;
    PImpl *impl_;
};


}
#define REGISTER_COMPONENT(Type) template void hive::World::add_component<Type>(int , Type); template Type& hive::World::get_component<Type>(int);

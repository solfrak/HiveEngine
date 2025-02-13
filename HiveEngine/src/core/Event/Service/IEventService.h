#pragma once
#include <functional>
#include <memory>


namespace hive
{
    struct Event;
    using MessageCallack = std::function<void(Event &event)>;

    class IEventService
    {
    public:
        virtual ~IEventService() {}
        static IEventService* get_singleton() {
            return s_instance;
        };

        virtual void Subscribe(MessageCallack callback) = 0;

        virtual void PushEvent(const Event &event) = 0;
        virtual void FlushEvents() = 0;

    protected:
        static IEventService* s_instance;
    };

}

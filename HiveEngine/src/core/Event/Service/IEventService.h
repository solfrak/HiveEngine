#pragma once
#include <functional>
#include <memory>



namespace hive
{
    struct Event;
    enum class EventCategory;
    using MessageCallack = std::function<void(Event &event)>;

    class IEventService
    {
    public:
        virtual ~IEventService() = default;
        static IEventService* get_singleton() {
            return s_instance;
        };

        virtual void Subscribe(EventCategory category, MessageCallack callback) = 0;

        virtual void PushEvent(EventCategory category, const Event &event) = 0;
        virtual void FlushEvents() = 0;

    protected:
        static IEventService* s_instance;
    };

}

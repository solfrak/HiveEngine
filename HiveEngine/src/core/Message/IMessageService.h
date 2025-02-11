#pragma once
#include <functional>
#include <memory>

namespace hive
{
    class Event;
}

namespace hive
{
    using MessageCallack = std::function<void(std::shared_ptr<Event> &event)>;

    class IEventService
    {
    public:
        virtual ~IEventService() {}

        virtual void Subscribe(MessageCallack callback) = 0;

        virtual void PushEvent(const std::shared_ptr<Event> &event) = 0;
        virtual void FlushEvents() = 0;
    };
}

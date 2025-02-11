#pragma once
#include <core/Event/EventVisitor.h>

namespace hive
{
    class Event;
}

namespace hive
{
    class Input final : public EventVisitor
    {
    public:
        void event_callback(std::shared_ptr<Event> &event);

        void handle(const MouseMotionEvent &event) override;
        void handle(const MouseButtonEvent &event) override;
    };
}

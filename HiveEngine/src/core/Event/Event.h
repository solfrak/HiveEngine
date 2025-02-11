#pragma once

namespace hive
{
    class Event
    {
    public:
        virtual ~Event() {}
        virtual void process(class EventVisitor& visitor) = 0;
    };
}
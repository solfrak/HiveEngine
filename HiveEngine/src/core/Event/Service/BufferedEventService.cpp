#include "BufferedEventService.h"
#include <cassert>

hive::BufferEventService::BufferEventService()
{
    assert(s_instance == nullptr);
    s_instance = this;
}

hive::BufferEventService::~BufferEventService()
{
    s_instance = nullptr;
}

void hive::BufferEventService::Subscribe(MessageCallack callback)
{
    m_eventCallbacks.push_back(callback);
}

void hive::BufferEventService::PushEvent(const std::shared_ptr<Event> &event)
{
    m_events.push_back(event);
}

void hive::BufferEventService::FlushEvents()
{
    for (auto &event : m_events)
    {
        for (auto &callback : m_eventCallbacks)
        {
            callback(event);
        }
    }

    m_events.clear();
}

#include "BufferedEventService.h"
#include <core/Event/Event.h>
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

void hive::BufferEventService::Subscribe(EventCategory category, MessageCallack callback)
{
    m_eventCallbacks[category].push_back(callback);
}

void hive::BufferEventService::PushEvent(EventCategory category, const Event &event)
{
    m_events.emplace_back(std::make_pair(category, event));
}

void hive::BufferEventService::FlushEvents()
{
    for (auto [category, event] : m_events)
    {
        for (auto &callback : m_eventCallbacks[category])
        {
            callback(event);
        }
    }

    m_events.clear();
}

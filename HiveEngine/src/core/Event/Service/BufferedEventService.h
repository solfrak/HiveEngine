#pragma once
#include "core/Event/Service/IEventService.h"
#include <unordered_map>

namespace hive
{
    class BufferEventService final : public IEventService
    {
    public:
        BufferEventService();
        ~BufferEventService() override;

        void Subscribe(EventCategory category, MessageCallack callback) override;
        void PushEvent(EventCategory category, const Event &event) override;
        void FlushEvents() override;

    private:
        std::vector<std::pair<EventCategory, Event>> m_events;
        std::unordered_map<EventCategory, std::vector<MessageCallack>> m_eventCallbacks;
    };
}


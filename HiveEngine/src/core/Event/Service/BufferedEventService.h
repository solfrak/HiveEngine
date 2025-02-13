#pragma once
#include "core/Event/Service/IEventService.h"

namespace hive
{
    class BufferEventService final : public IEventService
    {
    public:
        BufferEventService();
        ~BufferEventService();
        void Subscribe(MessageCallack callback) override;
        void PushEvent(const Event &event) override;
        void FlushEvents() override;

    private:
        std::vector<Event> m_events;
        std::vector<MessageCallack> m_eventCallbacks;
    };
}


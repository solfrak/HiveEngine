#pragma once
#include "core/Message/IMessageService.h"

namespace hive
{
    class BufferEventService final : public IEventService
    {
    public:
        void Subscribe(MessageCallack callback) override;
        void PushEvent(const std::shared_ptr<Event> &event) override;
        void FlushEvents() override;

    private:
        std::vector<std::shared_ptr<Event>> m_events;
        std::vector<MessageCallack> m_eventCallbacks;
    };
}


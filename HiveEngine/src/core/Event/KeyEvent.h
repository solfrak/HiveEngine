#pragma once
#include "Event.h"

namespace hive
{
    class KeyEvent : public Event
    {
    public:
        explicit KeyEvent(const int keycode) : m_key(keycode) {}

        [[nodiscard]] int GetKey() const { return m_key; }

        void process(::hive::EventVisitor &visitor) override;

    private:
        int m_key;
    };
}

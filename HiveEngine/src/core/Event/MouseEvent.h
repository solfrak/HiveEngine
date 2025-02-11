#pragma once

#include "Event.h"

namespace hive
{
    class MouseMotionEvent final : public Event
    {
    public:
        MouseMotionEvent(const int x, const int y) : m_x(x), m_y(y) {}

        [[nodiscard]] int GetX() const { return m_x; }
        [[nodiscard]] int GetY() const { return m_y; }

        void process(EventVisitor &visitor) override;

    private:
        int m_x, m_y;
    };

    class MouseButtonEvent final : public Event
    {
    public:
        MouseButtonEvent(const int button, const bool state) : m_button(button), m_state(state) {}

        [[nodiscard]] int GetButton() const { return m_button; }
        [[nodiscard]] bool GetState() const { return m_state; }

        void process(EventVisitor &visitor) override;

    private:
        int m_button;
        bool m_state;

    };

}

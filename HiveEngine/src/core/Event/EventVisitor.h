#pragma once
namespace hive
{
    class MouseMotionEvent;
    class MouseButtonEvent;
    class KeyEvent;

    class EventVisitor
    {
    public:
        virtual ~EventVisitor() {}
        virtual void handle(const MouseMotionEvent &event) = 0;
        virtual void handle(const MouseButtonEvent &event) = 0;
        virtual void handle(const KeyEvent &event) = 0;
    };


}

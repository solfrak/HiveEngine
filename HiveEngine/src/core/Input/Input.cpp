//
// Created by samuel on 10/02/25.
//

#include "Input.h"
#include "core/Logger.h"
#include "core/Event/MouseEvent.h"

void hive::Input::event_callback(std::shared_ptr<Event> &event)
{
    event->process(*this);
}

void hive::Input::handle(const MouseMotionEvent &event)
{
    LOG_INFO("Mouse motion event: %d, %d", event.GetX(), event.GetY());
}

void hive::Input::handle(const MouseButtonEvent &event)
{
    LOG_INFO("Mouse button event: %d, %b", event.GetButton(), event.GetState());
}

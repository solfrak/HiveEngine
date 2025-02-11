//
// Created by samuel on 10/02/25.
//

#include "Input.h"

#include <core/Event/Service/IEventService.h>
#include <core/Event/KeyEvent.h>

#include "core/Logger.h"
#include "core/Event/MouseEvent.h"

hive::Input::Input()
{
    IEventService::get_singleton()->Subscribe(std::bind(&Input::event_callback, this, std::placeholders::_1));
}

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

void hive::Input::handle(const KeyEvent &event)
{
    LOG_INFO("Key button was pressed or released: %d", event.GetKey());
}

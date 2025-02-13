//
// Created by samuel on 10/02/25.
//

#include "Input.h"

#include <core/Event/Service/IEventService.h>
#include <core/Event/Event.h>
#include "core/Logger.h"

#include <cassert>

static hive::Input* g_Input = nullptr;
hive::Input::Input()
{
    assert(g_Input == nullptr);
    g_Input = this;
    IEventService::get_singleton()->Subscribe(std::bind(&Input::event_callback, this, std::placeholders::_1));
}

hive::Input * hive::Input::get_singleton()
{
    return g_Input;
}

bool hive::Input::get_key(const HiveKeyCode key) const
{
    assert(key < MAX_KEYS);
    return m_keys[key].state;
}

bool hive::Input::get_key_pressed(const HiveKeyCode key) const
{
    assert(key < MAX_KEYS);
    return m_keys[key].is_pressed;
}

bool hive::Input::get_key_released(const HiveKeyCode key) const
{
    assert(key < MAX_KEYS);
    return m_keys[key].is_released;
}

bool hive::Input::get_mouse_button(const i8 button) const
{
    assert(button < MAX_MOUSE_BUTTON);
    return m_mouse_button[button].state;

}

bool hive::Input::get_mouse_button_pressed(const i8 button) const
{
    assert(button < MAX_MOUSE_BUTTON);
    return m_mouse_button[button].is_pressed;
}

bool hive::Input::get_mouse_button_released(const i8 button) const
{
    assert(button < MAX_MOUSE_BUTTON);
    return m_mouse_button[button].is_released;
}

f64 hive::Input::get_mouse_x() const
{
    return m_mouse_x;
}

f64 hive::Input::get_mouse_y() const
{
    return m_mouse_y;
}

void hive::Input::handle_mouse_move(const f64 x, const f64 y)
{
    m_mouse_x = x;
    m_mouse_y = y;
}

void hive::Input::handle_mouse_scroll(f64 x, f64 y)
{
    m_mouse_scroll_x = x;
    m_mouse_scroll_y = y;
}

void hive::Input::handle_mouse_button(const i8 button, const bool state)
{
    m_mouse_button[button] = {.state = state, .is_pressed = state, .is_released = !state};
}

void hive::Input::handle_key_button(const i8 button, const bool state)
{
    m_keys[button] = {.state = state, .is_pressed = state, .is_released = !state};
}

void hive::Input::update()
{
    for (i32 i = 0; i < MAX_KEYS; ++i)
    {
        m_keys[i].is_pressed = false;
        m_keys[i].is_released = false;
    }

    for (i32 i = 0; i < MAX_MOUSE_BUTTON; ++i)
    {
        m_mouse_button[i].is_pressed = false;
        m_mouse_button[i].is_released = false;
    }
}

void hive::Input::event_callback(const Event &event)
{
    switch (event.type)
    {
        case EventType::MouseMove:
            handle_mouse_move(event.data.f_64[0], event.data.f_64[1]);
            break;
        case EventType::MouseButtonDown:
            handle_mouse_button(event.data.i_32[0], true);
            break;
        case EventType::MouseButtonUp:
            handle_mouse_button(event.data.i_32[0], false);
            break;
        case EventType::MouseScroll:
            handle_mouse_scroll(event.data.f_64[0], event.data.f_64[1]);
            break;
        case EventType::KeyPressed:
            handle_key_button(event.data.i_32[0], true);
            break;
        case EventType::KeyReleased:
            handle_key_button(event.data.i_32[0], false);
            break;
        default: LOG_ERROR("Unhandled event type");
    }
}



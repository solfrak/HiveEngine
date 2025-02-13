#pragma once
#include <hvpch.h>


namespace hive
{
    struct Event;


    struct Button
    {
        bool state;
        bool is_pressed;
        bool is_released;
    };

    enum HiveKeyCode
    {
        HIVE_KEY_UNKNOWN,
        HIVE_KEY_SPACE,
        HIVE_KEY_APOSTROPHE,
        HIVE_KEY_COMMA,
        HIVE_KEY_MINUS,
        HIVE_KEY_PERIOD,
        HIVE_KEY_SLASH,
        HIVE_KEY_0,
        HIVE_KEY_1,
        HIVE_KEY_2,
        HIVE_KEY_3,
        HIVE_KEY_4,
        HIVE_KEY_5,
        HIVE_KEY_6,
        HIVE_KEY_7,
        HIVE_KEY_8,
        HIVE_KEY_9,
        HIVE_KEY_SEMICOLON,
        HIVE_KEY_EQUAL,
        HIVE_KEY_A,
        HIVE_KEY_B,
        HIVE_KEY_C,
        HIVE_KEY_D,
        HIVE_KEY_E,
        HIVE_KEY_F,
        HIVE_KEY_G,
        HIVE_KEY_H,
        HIVE_KEY_I,
        HIVE_KEY_J,
        HIVE_KEY_K,
        HIVE_KEY_L,
        HIVE_KEY_M,
        HIVE_KEY_N,
        HIVE_KEY_O,
        HIVE_KEY_P,
        HIVE_KEY_Q,
        HIVE_KEY_R,
        HIVE_KEY_S,
        HIVE_KEY_T,
        HIVE_KEY_U,
        HIVE_KEY_V,
        HIVE_KEY_W,
        HIVE_KEY_X,
        HIVE_KEY_Y,
        HIVE_KEY_Z,
        HIVE_KEY_LEFT_BRACKET,
        HIVE_KEY_BACKSLASH,
        HIVE_KEY_RIGHT_BRACKET,
        HIVE_KEY_GRAVE_ACCENT,
        HIVE_KEY_WORLD_1,
        HIVE_KEY_WORLD_2,

        /* Function keys */
        HIVE_KEY_ESCAPE,
        HIVE_KEY_ENTER,
        HIVE_KEY_TAB,
        HIVE_KEY_BACKSPACE,
        HIVE_KEY_INSERT,
        HIVE_KEY_DELETE,
        HIVE_KEY_RIGHT,
        HIVE_KEY_LEFT,
        HIVE_KEY_DOWN,
        HIVE_KEY_UP,
        HIVE_KEY_PAGE_UP,
        HIVE_KEY_PAGE_DOWN,
        HIVE_KEY_HOME,
        HIVE_KEY_END,
        HIVE_KEY_CAPS_LOCK,
        HIVE_KEY_SCROLL_LOCK,
        HIVE_KEY_NUM_LOCK,
        HIVE_KEY_PRINT_SCREEN,
        HIVE_KEY_PAUSE,
        HIVE_KEY_F1,
        HIVE_KEY_F2,
        HIVE_KEY_F3,
        HIVE_KEY_F4,
        HIVE_KEY_F5,
        HIVE_KEY_F6,
        HIVE_KEY_F7,
        HIVE_KEY_F8,
        HIVE_KEY_F9,
        HIVE_KEY_F10,
        HIVE_KEY_F11,
        HIVE_KEY_F12,
        HIVE_KEY_F13,
        HIVE_KEY_F14,
        HIVE_KEY_F15,
        HIVE_KEY_F16,
        HIVE_KEY_F17,
        HIVE_KEY_F18,
        HIVE_KEY_F19,
        HIVE_KEY_F20,
        HIVE_KEY_F21,
        HIVE_KEY_F22,
        HIVE_KEY_F23,
        HIVE_KEY_F24,
        HIVE_KEY_F25,
        HIVE_KEY_KP_0,
        HIVE_KEY_KP_1,
        HIVE_KEY_KP_2,
        HIVE_KEY_KP_3,
        HIVE_KEY_KP_4,
        HIVE_KEY_KP_5,
        HIVE_KEY_KP_6,
        HIVE_KEY_KP_7,
        HIVE_KEY_KP_8,
        HIVE_KEY_KP_9,
        HIVE_KEY_KP_DECIMAL,
        HIVE_KEY_KP_DIVIDE,
        HIVE_KEY_KP_MULTIPLY,
        HIVE_KEY_KP_SUBTRACT,
        HIVE_KEY_KP_ADD,
        HIVE_KEY_KP_ENTER,
        HIVE_KEY_KP_EQUAL,
        HIVE_KEY_LEFT_SHIFT,
        HIVE_KEY_LEFT_CONTROL,
        HIVE_KEY_LEFT_ALT,
        HIVE_KEY_LEFT_SUPER,
        HIVE_KEY_RIGHT_SHIFT,
        HIVE_KEY_RIGHT_CONTROL,
        HIVE_KEY_RIGHT_ALT,
        HIVE_KEY_RIGHT_SUPER,
        HIVE_KEY_MENU,
    };
#define HIVE_KEY_MAX 120

    class Input
    {
    public:
        Input();

        static Input* get_singleton();


        bool get_key(HiveKeyCode key) const;
        bool get_key_pressed(HiveKeyCode key) const;
        bool get_key_released(HiveKeyCode key) const;

        bool get_mouse_button(i8 button) const;
        bool get_mouse_button_pressed(i8 button) const;
        bool get_mouse_button_released(i8 button) const;

        f64 get_mouse_x() const;
        f64 get_mouse_y() const;


    protected:
        void event_callback(const Event &event);

        void handle_mouse_move(f64 x, f64 y);
        void handle_mouse_scroll(f64 x, f64 y);
        void handle_mouse_button(i8 button, bool state);
        void handle_key_button(i8 button, bool state);

    private:

        static constexpr i16 MAX_KEYS = 256;
        static constexpr i16 MAX_MOUSE_BUTTON = 8;
        Button m_keys[MAX_KEYS];
        Button m_mouse_button[MAX_MOUSE_BUTTON];
        f64 m_mouse_x, m_mouse_y;
        f64 m_mouse_scroll_x, m_mouse_scroll_y;


    private:
        friend class Application;
        void update();

    };
}

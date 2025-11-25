#pragma once
#include <wayland-client.h>
#include <X11/Xlib.h>

namespace swarm
{
    enum class DisplayServer
    {
        WAYLAND, X11
    };

    struct WindowHandleLinux
    {
        union
        {
            struct
            {
                wl_display *m_Display{nullptr};
                wl_surface *m_Surface{nullptr};
            } wayland{};

            struct
            {
                Display* m_Display{nullptr};
                Window m_Window{0};
            } x11;
        };

        DisplayServer m_DisplayServer{DisplayServer::WAYLAND};
    };
}

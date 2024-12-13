#include <hvpch.h>

#if defined(HIVE_PLATFORM_WINDOWS) && defined(HIVE_WINDOWING_RAYLIB)
#include <Core/WIndow/Window.h>
#include <raylib.h>
namespace hive
{
    Window::Window(i32 width, i32 height, const std::string &title, u32 flags)
    {
        InitWindow(width, height, title.c_str());

        flags_ = flags;
        handle_ = GetWindowHandle();
    }

    void Window::pollEvents()
    {
        PollInputEvents();
    }

    bool Window::shouldClose() const
    {
        return flags_ & FLAG_WINDOW_CLOSE;
    }

    void Window::setShouldClose(const bool state)
    {
        flags_ |= (state << 31);
    }
}

#endif

#pragma once

#include <hvpch.h>

#include <string>
namespace hive
{
    //The window is platform specific. Each supported OS will need it's own implementation in the platform folder (Platform/x/x_window.cpp)

    constexpr u32 FLAG_WINDOW_RESIZABLE = 1 << 0;
    constexpr u32 FLAG_WINDOW_DECORATED = 1 << 1;

    constexpr u32 FLAG_WINDOW_CLOSE = 1 << 31;


    class Window
    {
    public:
        Window(i32 width, i32 height, const std::string &title, u32 flags);

        void pollEvents();

        //Getter & Setter
        [[nodiscard]] bool shouldClose() const;
        void setShouldClose(bool state);



    private:
        u32 flags_;
        void* handle_;
    };
}

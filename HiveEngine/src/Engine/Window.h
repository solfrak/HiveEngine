//
// Created by GuillaumeIsCoding on 7/26/2024.
//
#pragma once
#include "hvpch.h"
#include "WindowConfiguration.h"


namespace hive
{
    struct WindowNativeData
    {
        void* window_handle;
        size_t sizeof_ptr;
        enum WindowBackend
        {
            RAYLIB
        };

        WindowBackend backend;
    };

    class HAPI Window {
    public:
        void init(const char* title, int width, int height, WindowConfiguration config);
        ~Window();

        [[nodiscard]] int getHeight() const;
        [[nodiscard]] WindowNativeData getNativeWindowData() const;
        [[nodiscard]] int getWidth() const;
        void onUpdate() const;
        void setIcon(unsigned char* data, int width, int height) const;
        [[nodiscard]] bool shouldClose() const;
        void updateConfiguration(WindowConfiguration configuration);
        WindowConfiguration getConfiguration() const;
    private:
        WindowConfiguration m_config;
    };
}

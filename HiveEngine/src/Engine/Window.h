//
// Created by GuillaumeIsCoding on 7/26/2024.
//
#pragma once
#include <hvpch.h>
#include <Engine/WindowConfiguration.h>


namespace hive
{
	enum WindowBackend
	{
		RAYLIB
	};

    struct WindowNativeData
    {
        void* window_handle;
        size_t sizeof_ptr;

        WindowBackend backend;
    };

    class HAPI Window {
    public:
        void init(const char* title, int width, int height, WindowConfiguration config);
        ~Window();

        [[nodiscard]] int getHeight() const;
        [[nodiscard]] int getWidth() const;
        [[nodiscard]] WindowNativeData getNativeWindowData() const;
        [[nodiscard]] bool shouldClose() const;
        [[nodiscard]] WindowConfiguration getConfiguration() const;

        void setIcon(unsigned char* data, int width, int height) const;
        void updateConfiguration(WindowConfiguration configuration);
    private:
        WindowConfiguration m_config;
    };
}

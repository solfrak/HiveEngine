//
// Created by samuel on 11/13/24.
//
#pragma once
#include "hvpch.h"

#ifdef HIVE_RAYLIB_ENABLED
#include <Engine/Window.h>


namespace hive
{
	class WindowRaylib : public Window
	{
	public:
		WindowRaylib(const char* title, int width, int height, WindowConfiguration config);
		~WindowRaylib() override;
		[[nodiscard]] int getHeight() const override;
		[[nodiscard]] WindowNativeData getNativeWindowData() const override;
		[[nodiscard]] int getWidth() const override;
		void onUpdate() const override;
		void setIcon(unsigned char* data, int width, int height) const override;
		[[nodiscard]] bool shouldClose() const override;
		void updateConfiguration(WindowConfiguration configuration) override;
		WindowConfiguration getConfiguration() override;

	private:
		WindowConfiguration m_config;
	};

}
#endif
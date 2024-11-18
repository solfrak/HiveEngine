//
// Created by samuel on 9/16/24.
//

#include "WindowFactory.h"

#include "WindowConfiguration.h"
#include "core/Memory/Memory.h"

#ifdef HIVE_RAYLIB_ENABLED
#include "platform/raylib/WindowRaylib.h"
hive::Window *hive::WindowFactory::Create(const std::string &title, const int width, const int height,
                                          const WindowConfiguration configuration) {
    return Create(title.c_str(), width, height, configuration);
}

hive::Window* hive::WindowFactory::Create(const char* title, const int width, const int height,
                                          const WindowConfiguration configuration)
{
	Window* ptr = static_cast<WindowRaylib*>(hmalloc(sizeof(WindowRaylib)));
	new (ptr) WindowRaylib(title, width, height, configuration);
	return  ptr;
}

#endif

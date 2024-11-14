//
// Created by samuel on 9/16/24.
//

#include "WindowFactory.h"

#include "WindowConfiguration.h"

#ifdef HIVE_RAYLIB_ENABLED
#include "platform/raylib/WindowRaylib.h"
hive::Window *hive::WindowFactory::Create(const std::string &title, const int width, const int height,
                                          const WindowConfiguration configuration) {
    return Create(title.c_str(), width, height, configuration);
}

hive::Window* hive::WindowFactory::Create(const char* title, const int width, const int height,
                                          const WindowConfiguration configuration)
{
	return new WindowRaylib(title, width, height, configuration);
}

#endif

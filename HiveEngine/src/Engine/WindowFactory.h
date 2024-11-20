//
// Created by samuel on 9/16/24.
//

#pragma once
#include "hvpch.h"

namespace hive {
    class Window;
    class WindowConfiguration;
}

namespace hive {
    class HAPI WindowFactory {
    public:
        static Window* Create(const std::string &title, int width, int height, WindowConfiguration configuration);
        static Window* Create(const char* title, int width, int height, WindowConfiguration configuration);
    };
}

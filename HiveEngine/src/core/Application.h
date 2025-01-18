#pragma once
#include <optional>
#include <rendering/GraphicsDevice.h>

#include "core/Memory.h"
#include "core/Logger.h"
#include "core/Window.h"

namespace hive
{

    struct ApplicationConfig
    {
        Logger::LogLevel log_level;
        WindowConfig window_config;
    };


    class Application
    {
    public:
        explicit Application(const ApplicationConfig &config);

        virtual ~Application();
        void run();

    protected:
        virtual bool on_init() = 0;
        virtual bool on_update(float delta_time) = 0;
        virtual bool on_destroy() = 0;

        Memory memory_;
        Window window_;
        GraphicsDevice *device_ = nullptr;

        bool app_should_close_ = false;
    };
}

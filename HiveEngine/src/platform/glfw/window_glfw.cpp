#define GLFW_INCLUDE_VULKAN
#include <core/Window.h>
#include <core/Logger.h>
#include <GLFW/glfw3.h>
#include "window_glfw.h"

#include <core/Event/Event.h>
#include <core/Event/Service/IEventService.h>
#include <core/Input/Input.h>

#include <array>

constexpr int GLFW_KEY_MAX = GLFW_KEY_LAST + 1;

// Create the lookup table
constexpr std::array<hive::HiveKeyCode, GLFW_KEY_MAX> keyMap = [] {
    std::array<hive::HiveKeyCode, GLFW_KEY_MAX> table{};

    // Initialize all keys as unknown
    table.fill(hive::HIVE_KEY_UNKNOWN);

    // Populate known mappings
    table[GLFW_KEY_SPACE] = hive::HIVE_KEY_SPACE;
    table[GLFW_KEY_APOSTROPHE] = hive::HIVE_KEY_APOSTROPHE;
    table[GLFW_KEY_COMMA] = hive::HIVE_KEY_COMMA;
    table[GLFW_KEY_MINUS] = hive::HIVE_KEY_MINUS;
    table[GLFW_KEY_PERIOD] = hive::HIVE_KEY_PERIOD;
    table[GLFW_KEY_SLASH] = hive::HIVE_KEY_SLASH;
    table[GLFW_KEY_0] = hive::HIVE_KEY_0;
    table[GLFW_KEY_1] = hive::HIVE_KEY_1;
    table[GLFW_KEY_2] = hive::HIVE_KEY_2;
    table[GLFW_KEY_3] = hive::HIVE_KEY_3;
    table[GLFW_KEY_4] = hive::HIVE_KEY_4;
    table[GLFW_KEY_5] = hive::HIVE_KEY_5;
    table[GLFW_KEY_6] = hive::HIVE_KEY_6;
    table[GLFW_KEY_7] = hive::HIVE_KEY_7;
    table[GLFW_KEY_8] = hive::HIVE_KEY_8;
    table[GLFW_KEY_9] = hive::HIVE_KEY_9;
    table[GLFW_KEY_A] = hive::HIVE_KEY_A;
    table[GLFW_KEY_B] = hive::HIVE_KEY_B;
    table[GLFW_KEY_C] = hive::HIVE_KEY_C;
    table[GLFW_KEY_D] = hive::HIVE_KEY_D;
    table[GLFW_KEY_E] = hive::HIVE_KEY_E;
    table[GLFW_KEY_F] = hive::HIVE_KEY_F;
    table[GLFW_KEY_G] = hive::HIVE_KEY_G;
    table[GLFW_KEY_H] = hive::HIVE_KEY_H;
    table[GLFW_KEY_I] = hive::HIVE_KEY_I;
    table[GLFW_KEY_J] = hive::HIVE_KEY_J;
    table[GLFW_KEY_K] = hive::HIVE_KEY_K;
    table[GLFW_KEY_L] = hive::HIVE_KEY_L;
    table[GLFW_KEY_M] = hive::HIVE_KEY_M;
    table[GLFW_KEY_N] = hive::HIVE_KEY_N;
    table[GLFW_KEY_O] = hive::HIVE_KEY_O;
    table[GLFW_KEY_P] = hive::HIVE_KEY_P;
    table[GLFW_KEY_Q] = hive::HIVE_KEY_Q;
    table[GLFW_KEY_R] = hive::HIVE_KEY_R;
    table[GLFW_KEY_S] = hive::HIVE_KEY_S;
    table[GLFW_KEY_T] = hive::HIVE_KEY_T;
    table[GLFW_KEY_U] = hive::HIVE_KEY_U;
    table[GLFW_KEY_V] = hive::HIVE_KEY_V;
    table[GLFW_KEY_W] = hive::HIVE_KEY_W;
    table[GLFW_KEY_X] = hive::HIVE_KEY_X;
    table[GLFW_KEY_Y] = hive::HIVE_KEY_Y;
    table[GLFW_KEY_Z] = hive::HIVE_KEY_Z;
    table[GLFW_KEY_ESCAPE] = hive::HIVE_KEY_ESCAPE;
    table[GLFW_KEY_ENTER] = hive::HIVE_KEY_ENTER;
    table[GLFW_KEY_TAB] = hive::HIVE_KEY_TAB;
    table[GLFW_KEY_BACKSPACE] = hive::HIVE_KEY_BACKSPACE;
    table[GLFW_KEY_RIGHT] = hive::HIVE_KEY_RIGHT;
    table[GLFW_KEY_LEFT] = hive::HIVE_KEY_LEFT;
    table[GLFW_KEY_DOWN] = hive::HIVE_KEY_DOWN;
    table[GLFW_KEY_UP] = hive::HIVE_KEY_UP;
    table[GLFW_KEY_F1] = hive::HIVE_KEY_F1;
    table[GLFW_KEY_F2] = hive::HIVE_KEY_F2;
    table[GLFW_KEY_F3] = hive::HIVE_KEY_F3;
    table[GLFW_KEY_F4] = hive::HIVE_KEY_F4;
    table[GLFW_KEY_F5] = hive::HIVE_KEY_F5;
    table[GLFW_KEY_F6] = hive::HIVE_KEY_F6;
    table[GLFW_KEY_F7] = hive::HIVE_KEY_F7;
    table[GLFW_KEY_F8] = hive::HIVE_KEY_F8;
    table[GLFW_KEY_F9] = hive::HIVE_KEY_F9;
    table[GLFW_KEY_F10] = hive::HIVE_KEY_F10;
    table[GLFW_KEY_F11] = hive::HIVE_KEY_F11;
    table[GLFW_KEY_F12] = hive::HIVE_KEY_F12;

    return table;
}();

// Lookup function
constexpr hive::HiveKeyCode GLFWToKeyCode(int glfwKey)
{
    if (glfwKey >= 0 && glfwKey < GLFW_KEY_MAX)
        return keyMap[glfwKey];
    return hive::HIVE_KEY_UNKNOWN;
}

hive::WindowGLFW::~WindowGLFW()
{
    LOG_INFO("Destroying GLFW Window");
    glfwDestroyWindow(window_);
}

hive::WindowGLFW::WindowGLFW(const WindowConfig &config)
{
    if (!glfwInit())
    {
        //TODO: error handling
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window_ = glfwCreateWindow(config.width, config.height, config.title, nullptr, nullptr);

    if (!window_)
    {
        //TODO: error handling
    }


    glfwSetWindowUserPointer(window_, IEventService::get_singleton());

    glfwSetKeyCallback(window_, [](GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        IEventService *service = static_cast<IEventService *>(glfwGetWindowUserPointer(window));
        Event event{};
        switch (action)
        {
            case GLFW_PRESS:
                event.type = EventType::KeyPressed;
            break;
            case GLFW_RELEASE:
                event.type = EventType::KeyReleased;
            break;
        }
        event.data.i_32[0] = GLFWToKeyCode(key);
        service->PushEvent(EventCategory::Input, event);
    });

    glfwSetMouseButtonCallback(window_, [](GLFWwindow *window, int button, int action, int mods)
    {
        IEventService *service = static_cast<IEventService *>(glfwGetWindowUserPointer(window));
        Event event{};
        switch (action)
        {
            case GLFW_PRESS:
                event.type = EventType::MouseButtonDown;
            break;
            case GLFW_RELEASE:
                event.type = EventType::MouseButtonUp;
            break;
        }
        event.data.i_32[0] = button;
        service->PushEvent(EventCategory::Input, event);
    });

    glfwSetCursorPosCallback(window_, [](GLFWwindow *window, double x, double y)
    {
        auto *service = static_cast<IEventService *>(glfwGetWindowUserPointer(window));
        Event event{};
        event.type = EventType::MouseMove;
        event.data.f_64[0] = x;
        event.data.f_64[1] = y;
        service->PushEvent(EventCategory::Input, event);
    });

    glfwSetScrollCallback(window_, [](GLFWwindow *window, double x, double y)
    {
        auto *service = static_cast<IEventService *>(glfwGetWindowUserPointer(window));
        Event event{};
        event.type = EventType::MouseScroll;
        event.data.f_64[0] = x;
        event.data.f_64[1] = y;
        service->PushEvent(EventCategory::Input, event);
    });

    glfwSetFramebufferSizeCallback(window_, [](GLFWwindow *window, int width, int height)
    {
        auto *service = static_cast<IEventService *>(glfwGetWindowUserPointer(window));
        Event event{};

        event.type = EventType::FramebufferResized;
        event.data.i_32[0] = width;
        event.data.i_32[1] = height;
        service->PushEvent(EventCategory::Rendering, event);
    });

}

u64 hive::WindowGLFW::getSizeof() const
{
    return sizeof(WindowGLFW);
}

bool hive::WindowGLFW::shouldClose() const
{
    return glfwWindowShouldClose(window_);
}

void hive::WindowGLFW::pollEvents()
{
    glfwPollEvents();
}

void hive::WindowGLFW::waitEvents() const
{
    glfwWaitEvents();
}

void hive::WindowGLFW::getFramebufferSize(i32 &width, i32 &height) const
{
    glfwGetFramebufferSize(window_, &width, &height);
}

#ifdef HIVE_BACKEND_VULKAN_SUPPORTED
void hive::WindowGLFW::appendRequiredVulkanExtension(std::vector<const char *> &vector) const
{
    u32 count;
    const char** extensions = glfwGetRequiredInstanceExtensions(&count);

    for (int i = 0; i < count; i++)
    {
        vector.emplace_back(extensions[i]);
    }
}

void hive::WindowGLFW::createVulkanSurface(void *instance, void *surface_khr) const
{
    auto vk_instance = static_cast<VkInstance>(instance);
    auto vk_surface = static_cast<VkSurfaceKHR*>(surface_khr);
    glfwCreateWindowSurface(vk_instance, window_, nullptr, vk_surface);
}




#endif

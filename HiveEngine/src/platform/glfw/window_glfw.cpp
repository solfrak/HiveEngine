#define GLFW_INCLUDE_VULKAN
#include <core/Window.h>
#include <core/Logger.h>
#include <GLFW/glfw3.h>
#include "window_glfw.h"

#include <core/Event/Event.h>
#include <core/Event/Service/IEventService.h>
#include <core/Input/Input.h>

constexpr std::array<std::pair<int, hive::HiveKeyCode>, HIVE_KEY_MAX> keyMap = {{
    {GLFW_KEY_SPACE, hive::HIVE_KEY_SPACE},
    {GLFW_KEY_APOSTROPHE, hive::HIVE_KEY_APOSTROPHE},
    {GLFW_KEY_COMMA, hive::HIVE_KEY_COMMA},
    {GLFW_KEY_MINUS, hive::HIVE_KEY_MINUS},
    {GLFW_KEY_PERIOD, hive::HIVE_KEY_PERIOD},
    {GLFW_KEY_SLASH, hive::HIVE_KEY_SLASH},
    {GLFW_KEY_0, hive::HIVE_KEY_0},
    {GLFW_KEY_1, hive::HIVE_KEY_1},
    {GLFW_KEY_2, hive::HIVE_KEY_2},
    {GLFW_KEY_3, hive::HIVE_KEY_3},
    {GLFW_KEY_4, hive::HIVE_KEY_4},
    {GLFW_KEY_5, hive::HIVE_KEY_5},
    {GLFW_KEY_6, hive::HIVE_KEY_6},
    {GLFW_KEY_7, hive::HIVE_KEY_7},
    {GLFW_KEY_8, hive::HIVE_KEY_8},
    {GLFW_KEY_9, hive::HIVE_KEY_9},
    {GLFW_KEY_SEMICOLON, hive::HIVE_KEY_SEMICOLON},
    {GLFW_KEY_EQUAL, hive::HIVE_KEY_EQUAL},
    {GLFW_KEY_A, hive::HIVE_KEY_A},
    {GLFW_KEY_B, hive::HIVE_KEY_B},
    {GLFW_KEY_C, hive::HIVE_KEY_C},
    {GLFW_KEY_D, hive::HIVE_KEY_D},
    {GLFW_KEY_E, hive::HIVE_KEY_E},
    {GLFW_KEY_F, hive::HIVE_KEY_F},
    {GLFW_KEY_G, hive::HIVE_KEY_G},
    {GLFW_KEY_H, hive::HIVE_KEY_H},
    {GLFW_KEY_I, hive::HIVE_KEY_I},
    {GLFW_KEY_J, hive::HIVE_KEY_J},
    {GLFW_KEY_K, hive::HIVE_KEY_K},
    {GLFW_KEY_L, hive::HIVE_KEY_L},
    {GLFW_KEY_M, hive::HIVE_KEY_M},
    {GLFW_KEY_N, hive::HIVE_KEY_N},
    {GLFW_KEY_O, hive::HIVE_KEY_O},
    {GLFW_KEY_P, hive::HIVE_KEY_P},
    {GLFW_KEY_Q, hive::HIVE_KEY_Q},
    {GLFW_KEY_R, hive::HIVE_KEY_R},
    {GLFW_KEY_S, hive::HIVE_KEY_S},
    {GLFW_KEY_T, hive::HIVE_KEY_T},
    {GLFW_KEY_U, hive::HIVE_KEY_U},
    {GLFW_KEY_V, hive::HIVE_KEY_V},
    {GLFW_KEY_W, hive::HIVE_KEY_W},
    {GLFW_KEY_X, hive::HIVE_KEY_X},
    {GLFW_KEY_Y, hive::HIVE_KEY_Y},
    {GLFW_KEY_Z, hive::HIVE_KEY_Z},
    {GLFW_KEY_LEFT_BRACKET, hive::HIVE_KEY_LEFT_BRACKET},
    {GLFW_KEY_BACKSLASH, hive::HIVE_KEY_BACKSLASH},
    {GLFW_KEY_RIGHT_BRACKET, hive::HIVE_KEY_RIGHT_BRACKET},
    {GLFW_KEY_GRAVE_ACCENT, hive::HIVE_KEY_GRAVE_ACCENT},
    {GLFW_KEY_ESCAPE, hive::HIVE_KEY_ESCAPE},
    {GLFW_KEY_ENTER, hive::HIVE_KEY_ENTER},
    {GLFW_KEY_TAB, hive::HIVE_KEY_TAB},
    {GLFW_KEY_BACKSPACE, hive::HIVE_KEY_BACKSPACE},
    {GLFW_KEY_INSERT, hive::HIVE_KEY_INSERT},
    {GLFW_KEY_DELETE, hive::HIVE_KEY_DELETE},
    {GLFW_KEY_RIGHT, hive::HIVE_KEY_RIGHT},
    {GLFW_KEY_LEFT, hive::HIVE_KEY_LEFT},
    {GLFW_KEY_DOWN, hive::HIVE_KEY_DOWN},
    {GLFW_KEY_UP, hive::HIVE_KEY_UP},
    {GLFW_KEY_PAGE_UP, hive::HIVE_KEY_PAGE_UP},
    {GLFW_KEY_PAGE_DOWN, hive::HIVE_KEY_PAGE_DOWN},
    {GLFW_KEY_HOME, hive::HIVE_KEY_HOME},
    {GLFW_KEY_END, hive::HIVE_KEY_END},
    {GLFW_KEY_CAPS_LOCK, hive::HIVE_KEY_CAPS_LOCK},
    {GLFW_KEY_SCROLL_LOCK, hive::HIVE_KEY_SCROLL_LOCK},
    {GLFW_KEY_NUM_LOCK, hive::HIVE_KEY_NUM_LOCK},
    {GLFW_KEY_PRINT_SCREEN, hive::HIVE_KEY_PRINT_SCREEN},
    {GLFW_KEY_PAUSE, hive::HIVE_KEY_PAUSE},
    {GLFW_KEY_F1, hive::HIVE_KEY_F1},
    {GLFW_KEY_F2, hive::HIVE_KEY_F2},
    {GLFW_KEY_F3, hive::HIVE_KEY_F3},
    {GLFW_KEY_F4, hive::HIVE_KEY_F4},
    {GLFW_KEY_F5, hive::HIVE_KEY_F5},
    {GLFW_KEY_F6, hive::HIVE_KEY_F6},
    {GLFW_KEY_F7, hive::HIVE_KEY_F7},
    {GLFW_KEY_F8, hive::HIVE_KEY_F8},
    {GLFW_KEY_F9, hive::HIVE_KEY_F9},
    {GLFW_KEY_F10, hive::HIVE_KEY_F10},
    {GLFW_KEY_F11, hive::HIVE_KEY_F11},
    {GLFW_KEY_F12, hive::HIVE_KEY_F12},
    {GLFW_KEY_KP_0, hive::HIVE_KEY_KP_0},
    {GLFW_KEY_KP_1, hive::HIVE_KEY_KP_1},
    {GLFW_KEY_KP_2, hive::HIVE_KEY_KP_2},
    {GLFW_KEY_KP_3, hive::HIVE_KEY_KP_3},
    {GLFW_KEY_KP_4, hive::HIVE_KEY_KP_4},
    {GLFW_KEY_KP_5, hive::HIVE_KEY_KP_5},
    {GLFW_KEY_KP_6, hive::HIVE_KEY_KP_6},
    {GLFW_KEY_KP_7, hive::HIVE_KEY_KP_7},
    {GLFW_KEY_KP_8, hive::HIVE_KEY_KP_8},
    {GLFW_KEY_KP_9, hive::HIVE_KEY_KP_9},
    {GLFW_KEY_KP_DECIMAL, hive::HIVE_KEY_KP_DECIMAL},
    {GLFW_KEY_KP_DIVIDE, hive::HIVE_KEY_KP_DIVIDE},
    {GLFW_KEY_KP_MULTIPLY, hive::HIVE_KEY_KP_MULTIPLY},
    {GLFW_KEY_KP_SUBTRACT, hive::HIVE_KEY_KP_SUBTRACT},
    {GLFW_KEY_KP_ADD, hive::HIVE_KEY_KP_ADD},
    {GLFW_KEY_KP_ENTER, hive::HIVE_KEY_KP_ENTER},
    {GLFW_KEY_KP_EQUAL, hive::HIVE_KEY_KP_EQUAL},
    {GLFW_KEY_LEFT_SHIFT, hive::HIVE_KEY_LEFT_SHIFT},
    {GLFW_KEY_LEFT_CONTROL, hive::HIVE_KEY_LEFT_CONTROL},
    {GLFW_KEY_LEFT_ALT, hive::HIVE_KEY_LEFT_ALT},
    {GLFW_KEY_LEFT_SUPER, hive::HIVE_KEY_LEFT_SUPER},
    {GLFW_KEY_RIGHT_SHIFT, hive::HIVE_KEY_RIGHT_SHIFT},
    {GLFW_KEY_RIGHT_CONTROL, hive::HIVE_KEY_RIGHT_CONTROL},
    {GLFW_KEY_RIGHT_ALT, hive::HIVE_KEY_RIGHT_ALT},
    {GLFW_KEY_RIGHT_SUPER, hive::HIVE_KEY_RIGHT_SUPER},
    {GLFW_KEY_MENU, hive::HIVE_KEY_MENU}
}};


constexpr hive::HiveKeyCode GLFWToKeyCode(int glfwKey)
{
    for (const auto& [glfw, key] : keyMap)
    {
        if (glfw == glfwKey)
            return key;
    }

    return hive::HiveKeyCode::HIVE_KEY_UNKNOWN;
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
        service->PushEvent(event);
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
        service->PushEvent(event);
    });

    glfwSetCursorPosCallback(window_, [](GLFWwindow *window, double x, double y)
    {
        IEventService *service = static_cast<IEventService *>(glfwGetWindowUserPointer(window));
        Event event{};
        event.type = EventType::MouseMove;
        event.data.f_64[0] = x;
        event.data.f_64[1] = y;
        service->PushEvent(event);
    });

    glfwSetScrollCallback(window_, [](GLFWwindow *window, double x, double y)
    {
        IEventService *service = static_cast<IEventService *>(glfwGetWindowUserPointer(window));
        Event event{};
        event.type = EventType::MouseScroll;
        event.data.f_64[0] = x;
        event.data.f_64[1] = y;
        service->PushEvent(event);
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

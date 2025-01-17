#include <core/Logger.h>
#include <core/Application.h>
#include <rendering/Renderer.h>

#include <iostream>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



void RegisterDefaultLoggerSync(hive::Logger::LogLevel level)
{
    hive::Logger::AddSync(level, [](hive::Logger::LogLevel level, const char* msg)
    {
       std::cout << msg << std::endl;
    });
}

class BasicApp final : public hive::Application
{
public:
    explicit BasicApp(hive::ApplicationConfig &config)
        : Application(config)
    {
    }

protected:
    bool on_init() override;

    bool on_update(float delta_time) override;

    bool on_destroy() override;

private:
    hive::UniformBufferObjectHandle ubo_handle;
    hive::ShaderProgramHandle handles[3];
    i32 current_shader = 0;
    std::chrono::time_point<std::chrono::system_clock> begin_time;
};

bool BasicApp::on_init()
{
    ubo_handle = renderer_->createUbo();
    for (i32 i = 0; i < 3; ++i)
    {
        handles[i] = renderer_->createShader("shaders/vert.spv", "shaders/frag.spv", ubo_handle, i);
    }
    begin_time = std::chrono::high_resolution_clock::now();
    return true;
}

static auto startTime = std::chrono::high_resolution_clock::now();
void update_camera(hive::IRenderer &renderer, hive::UniformBufferObjectHandle handle)
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
    hive::UniformBufferObject ubo{};
    // ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.model = glm::mat4(1.0f);
    ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.proj = glm::perspective(glm::radians(45.0f),
                                1920 / (float) 1080, 0.1f, 10.0f);
    ubo.proj[1][1] *= -1;
    renderer.updateUbo(handle, ubo);
}

bool BasicApp::on_update(float delta_time)
{
    auto end_time = std::chrono::high_resolution_clock::now();
    if (end_time - begin_time > std::chrono::milliseconds(3000))
    {
        begin_time = end_time;

        renderer_->destroyShader(handles[current_shader]);
        current_shader = current_shader + 1;
        if (current_shader >= 3)
        {
            app_should_close_ = true;
            return true;
        }
    }
    update_camera(*renderer_, ubo_handle);

    if (!renderer_->beginDrawing()) return false;
    {
        renderer_->useShader(handles[current_shader]);
        renderer_->temp_draw();
    }
    if (!renderer_->endDrawing()) return false;
    if (!renderer_->frame()) return false;

    return true;
}

bool BasicApp::on_destroy()
{
    renderer_->destroyUbo(ubo_handle);
    return true;
}

int main()
{
    hive::Logger logger;
    RegisterDefaultLoggerSync(hive::Logger::LogLevel::DEBUG);

    hive::ApplicationConfig config{};

    config.log_level = hive::Logger::LogLevel::DEBUG;
    config.window_config.width = 1080;
    config.window_config.height = 920;
    config.window_config.title = "Hive Engine";
    config.window_config.type = hive::WindowConfig::WindowType::GLFW;

    // hive::Application app(config);
    BasicApp app(config);
    app.run();


}
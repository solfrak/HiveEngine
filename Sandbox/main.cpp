#include <core/Logger.h>
#include <core/Application.h>
#include <rendering/RenderType.h>

#include <iostream>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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

    void load_model();

private:
    hive::UniformBufferObjectHandle ubo_handle;
    hive::ShaderProgramHandle handles[3];
    i32 current_shader = 0;
    std::chrono::time_point<std::chrono::system_clock> begin_time;


    hive::Buffer vertex_buffer;
    hive::Buffer index_buffer;
    hive::Buffer ubo_buffer;
    hive::Texture texture;

    std::vector<hive::Vertex> vertices;
    std::vector<u32> indices;

    hive::Pipeline pipeline_;
};


bool BasicApp::on_init()
{
    // ubo_handle = renderer_->createUbo();
    // for (i32 i = 0; i < 3; ++i)
    // {
    //     handles[i] = renderer_->createShader("shaders/vert.spv", "shaders/frag.spv", ubo_handle, i);
    // }

    load_model();

    //Vertex buffer creation
    {
        hive::BufferDesc temp_desc{};
        temp_desc.usage_flag = hive::BufferDesc::UsageFlag::TRANSFER_SRC;
        temp_desc.mem_prop_flags = hive::BufferDesc::MemoryType::HOST_VISIBLE | hive::BufferDesc::HOST_COHERENT;
        temp_desc.size = sizeof(vertices[0]) * vertices.size();

        hive::Buffer temp_buffer;
        if (!device_->CreateBuffer(temp_desc, temp_buffer))
        {
            return false;
        }
        device_->FillBuffer(temp_buffer, vertices.data(), temp_desc.size);

        hive::BufferDesc vertex_buffer_desc{};
        vertex_buffer_desc.usage_flag = hive::BufferDesc::UsageFlag::TRANSFER_DST |
                                        hive::BufferDesc::UsageFlag::VERTEX_BUFFER;
        vertex_buffer_desc.mem_prop_flags = hive::BufferDesc::MemoryType::DEVICE_LOCAL;
        vertex_buffer_desc.size = temp_desc.size;

        if (!device_->CreateBuffer(vertex_buffer_desc, vertex_buffer))
        {
            return false;
        }

        device_->CopyBuffer(temp_buffer, vertex_buffer);
        device_->DestroyBuffer(temp_buffer);
    }

    //Index buffer
    {
        hive::BufferDesc temp_desc{};
        temp_desc.usage_flag = hive::BufferDesc::UsageFlag::TRANSFER_SRC;
        temp_desc.mem_prop_flags = hive::BufferDesc::MemoryType::HOST_VISIBLE | hive::BufferDesc::MemoryType::HOST_COHERENT;
        temp_desc.size = indices.size() * sizeof(indices[0]);

        hive::Buffer temp_buffer{};
        if(!device_->CreateBuffer(temp_desc, temp_buffer))
        {
            return false;
        }
        device_->FillBuffer(temp_buffer, indices.data(), temp_desc.size);
        hive::BufferDesc index_buffer_desc{};
        index_buffer_desc.usage_flag = hive::BufferDesc::UsageFlag::TRANSFER_DST | hive::BufferDesc::UsageFlag::INDEX_BUFFER;
        index_buffer_desc.mem_prop_flags = hive::BufferDesc::MemoryType::DEVICE_LOCAL;
        index_buffer_desc.size = indices.size() * sizeof(indices[0]);
        if(!device_->CreateBuffer(index_buffer_desc, index_buffer))
        {
            return false;
        }
        device_->CopyBuffer(temp_buffer, index_buffer);
        device_->DestroyBuffer(temp_buffer);
    }

    //Ubo buffer
    {
        hive::BufferDesc ubo_desc{};
        ubo_desc.usage_flag = hive::BufferDesc::UsageFlag::UNIFORM_BUFFER;
        ubo_desc.mem_prop_flags = hive::BufferDesc::MemoryType::HOST_VISIBLE | hive::BufferDesc::MemoryType::HOST_COHERENT;
        ubo_desc.size = sizeof(hive::UniformBufferObject);

        if(!device_->CreateBuffer(ubo_desc, ubo_buffer))
        {
            return false;
        }
    }

    //Texture image
    {
        i32 texWidth, texHeight, texChannels;
        stbi_uc *pixels = stbi_load("textures/viking_room.png", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
        u32 image_size = texWidth * texHeight * 4;

        if (!pixels)
        {
            return false;
        }

        hive::BufferDesc temp_text_desc{};
        temp_text_desc.usage_flag = hive::BufferDesc::UsageFlag::TRANSFER_SRC;
        temp_text_desc.mem_prop_flags = hive::BufferDesc::MemoryType::HOST_VISIBLE | hive::BufferDesc::MemoryType::HOST_COHERENT;
        temp_text_desc.size = image_size;

        hive::Buffer temp_texture_buffer{};
        if(!device_->CreateBuffer(temp_text_desc, temp_texture_buffer))
        {
            return false;
        }
        device_->FillBuffer(temp_texture_buffer, pixels, image_size);
        stbi_image_free(pixels);

        hive::TextureDesc texture_desc{};
        texture_desc.width = texWidth;
        texture_desc.heigth = texHeight;
        texture_desc.nbr_channels = texChannels;
        texture_desc.format = hive::TextureDesc::Format::R8G8B8A8_SRGB;

        if (!device_->CreateTexture(texture_desc, temp_texture_buffer, texture))
        {
            return false;
        }

        device_->DestroyBuffer(temp_texture_buffer);
    }

    //Pipeline
    {
        hive::ShaderDesc vert_desc{};
        vert_desc.path = "shaders/vert.spv";
        vert_desc.stage = hive::ShaderStage::VERTEX;

        hive::Shader vert_module{};
        if(!device_->CreateShader(vert_desc, vert_module))
        {
            return false;
        }


        hive::ShaderDesc frag_desc{};
        frag_desc.path = "shaders/frag.spv";
        frag_desc.stage = hive::ShaderStage::FRAGMENT;

        hive::Shader frag_module{};
        if(!device_->CreateShader(frag_desc, frag_module))
        {
            return false;
        }

        hive::PipelineDesc pipeline_desc{};
        pipeline_desc.cull_mode = hive::PipelineDesc::CullMode::FILL;
        pipeline_desc.shaders_stages.push_back(vert_module);
        pipeline_desc.shaders_stages.push_back(frag_module);

        //TODO: Remove this and read config file instead to get the layout
        hive::PipelineLayout vertex_layout{};
        vertex_layout.stage = hive::ShaderStage::VERTEX;
        vertex_layout.type = hive::DescriptorType::UNIFORM_BUFFER;
        vertex_layout.binding_location = 0;

        hive::PipelineLayout frag_layout{};
        frag_layout.stage = hive::ShaderStage::FRAGMENT;
        frag_layout.type = hive::DescriptorType::SAMPLER2D;
        frag_layout.binding_location = 1;

        pipeline_desc.layouts.push_back(vertex_layout);
        pipeline_desc.layouts.push_back(frag_layout);

        if(!device_->CreatePipeline(pipeline_desc, pipeline_))
        {
            return false;
        }

        device_->DestroyShader(vert_module);
        device_->DestroyShader(frag_module);

        hive::PipelineDescriptorSetDesc desc_ubo{};
        desc_ubo.type = hive::DescriptorType::UNIFORM_BUFFER;
        desc_ubo.buffer.push_back(ubo_buffer);
        desc_ubo.binding_location = 0;

        device_->PipelineUpdateDescriptor(desc_ubo, pipeline_);

        hive::PipelineDescriptorSetDesc desc_sampler{};
        desc_sampler.type = hive::DescriptorType::SAMPLER2D;
        desc_sampler.textures.push_back(texture);
        desc_sampler.binding_location = 1;

        device_->PipelineUpdateDescriptor(desc_sampler, pipeline_);
    }

    return true;
}

static auto startTime = std::chrono::high_resolution_clock::now();
void update_camera(hive::GraphicsDevice &renderer, hive::Buffer &buffer)
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
    hive::UniformBufferObject ubo{};
    ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    // ubo.model = glm::mat4(1.0f);
    ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.proj = glm::perspective(glm::radians(45.0f),
                                1920 / (float) 1080, 0.1f, 10.0f);
    ubo.proj[1][1] *= -1;

    renderer.BufferUpdateData(buffer, &ubo);
}

bool BasicApp::on_update(float delta_time)
{

    update_camera(*device_, ubo_buffer);

    if (!device_->BeginCmd()) return false;
    {
        device_->CmdBindPipeline(pipeline_);
        device_->CmdDrawIndexed(vertex_buffer, index_buffer, indices.size());
    }
    if (!device_->EndCmd()) return false;

    if (!device_->SubmitFrame()) return false;
    return true;
}

bool BasicApp::on_destroy()
{
    // renderer_->destroyUbo(ubo_handle);
    device_->WaitForGPU();

    device_->DestroyTexture(texture);
    device_->DestroyBuffer(ubo_buffer);
    device_->DestroyBuffer(vertex_buffer);
    device_->DestroyBuffer(index_buffer);
    device_->DestroyPipeline(pipeline_);

    return true;
}

void BasicApp::load_model()
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, "assets/viking_room.obj")) {
        throw std::runtime_error(warn + err);
    }

    for(const auto& shape : shapes)
    {
        for(const auto& index : shape.mesh.indices)
        {
            hive::Vertex vertex{};
            vertex.pos = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            vertex.texCoord = {
                attrib.texcoords[2 * index.texcoord_index + 0],
                1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            };

            vertex.color = {1.0f, 1.0f, 1.0f};


            vertices.push_back(vertex);
            indices.push_back(indices.size());
        }
    }
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

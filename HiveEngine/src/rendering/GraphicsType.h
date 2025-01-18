#pragma once
#include <hvpch.h>
#include <string>
#include <vector>
namespace hive
{

    struct TextureDesc
    {
        u32 width, heigth;
        u8 nbr_channels;
        enum class Format
        {
            R8G8B8A8_SRGB
        };
        Format format;
    };

    struct Texture
    {
        TextureDesc desc;
        u32 id{};
    };


    struct BufferDesc
    {
        enum UsageFlag
        {
            TRANSFER_SRC = 1 << 0,
            TRANSFER_DST = 1 << 1,
            VERTEX_BUFFER = 1 << 2,
            INDEX_BUFFER = 1 << 3,
            UNIFORM_BUFFER = 1 << 4,
        };

        enum MemoryType
        {
            HOST_VISIBLE = 1 << 0,
            HOST_COHERENT = 1 << 1,
            DEVICE_LOCAL = 1 << 2,
        };

        u32 usage_flag;
        u32 mem_prop_flags;
        u32 size;

    };

    struct Buffer
    {
        u32 id;
        BufferDesc desc;
    };

    enum class ShaderStage
    {
        VERTEX, FRAGMENT
    };
    struct ShaderDesc
    {
        std::string path;


        ShaderStage stage;

    };

    struct Shader
    {
        ShaderDesc desc;
        void* local_data{};
    };

    enum class DescriptorType
    {
        UNIFORM_BUFFER, SAMPLER2D
    };
    struct PipelineLayout
    {

        DescriptorType type;
        u32 binding_location;
        ShaderStage stage;

    };

    struct PipelineDesc
    {
        std::vector<Shader> shaders_stages{};
        enum class CullMode
        {
            FILL, LINE, POINT
        };

        std::vector<PipelineLayout> layouts;
        CullMode cull_mode;

    };

    struct Pipeline
    {
        PipelineDesc desc;
        u32 id{};
    };

    struct PipelineDescriptorSetDesc
    {
        DescriptorType type{};
        std::vector<Buffer> buffer{};
        std::vector<Texture> textures{};
        u32 binding_location{};
    };



}
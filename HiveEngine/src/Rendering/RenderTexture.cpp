//
// Created by lapor on 11/23/2024.
//
#include "RenderTexture.h"

#ifdef HIVE_RAYLIB_ENABLED

#include <raylib.h>
hive::RenderTexture hive::CreateRenderTexture(int width, int height)
{
    auto raylib_target = LoadRenderTexture(width, height);
    RenderTexture result = {};
    result.id = raylib_target.id;

    const Texture color = { raylib_target.texture.id, raylib_target.texture.width, raylib_target.texture.height, raylib_target.texture.mipmaps, raylib_target.texture.format};
    const Texture depth = { raylib_target.depth.id, raylib_target.depth.width, raylib_target.depth.height, raylib_target.depth.mipmaps, raylib_target.depth.format};

    result.color = color;
    result.depth = depth;

    return result;
}

#endif

//
// Created by lapor on 11/23/2024.
//

#ifndef RENDERTEXTURE_H
#define RENDERTEXTURE_H
#include "Texture.h"

namespace hive
{
    //Framebuffer
    struct RenderTexture
    {
        unsigned int id;
        Texture color;
        Texture depth;
    };

    RenderTexture HAPI CreateRenderTexture(int width, int height);
}
#endif //RENDERTEXTURE_H

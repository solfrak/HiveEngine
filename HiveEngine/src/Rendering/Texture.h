//
// Created by lapor on 11/23/2024.
//

#ifndef TEXTURE_H
#define TEXTURE_H

namespace hive
{
    struct Texture
    {
        unsigned int id;
        int width, height;
        int mipmap, format;
    };
}
#endif //TEXTURE_H

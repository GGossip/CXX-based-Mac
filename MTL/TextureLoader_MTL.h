#ifndef _MTL_TEXTURELOADER_MTL_H_
#define _MTL_TEXTURELOADER_MTL_H_ 1

#include "../TextureLoader.h"

#include "../Headers_CXX/Metal_CXX.h"

struct TextureLoader_SpecificHeader
{
    MTLTextureType textureType;
    MTLPixelFormat pixelFormat;
    NSUInteger width;
    NSUInteger height;
    NSUInteger depth;
    NSUInteger mipmapLevelCount;
    NSUInteger arrayLength;
};

struct TextureLoader_SpecificHeader TextureLoader_ToSpecificHeader(struct TextureLoader_NeutralHeader const *neutral_texture_header);

#endif
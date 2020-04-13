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

struct TextureLoader_MTLBufferImageCopy
{
    NSUInteger sourceOffset;
    NSUInteger sourceBytesPerRow;
    NSUInteger sourceBytesPerImage;
    MTLSize sourceSize;
    NSUInteger destinationSlice;
    NSUInteger destinationLevel;
    MTLOrigin destinationOrigin;
};

size_t TextureLoader_GetCopyableFootprints(struct TextureLoader_SpecificHeader const *mtl_texture_header,
                                           uint32_t NumSubresources, struct TextureLoader_MemcpyDest *pDest, TextureLoader_MTLBufferImageCopy *pRegions);

#endif
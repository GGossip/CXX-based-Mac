#include "TextureLoader_MTL.h"

uint32_t TextureLoader_CalcSubresource(uint32_t mipLevel, uint32_t arrayLayer, uint32_t aspectIndex, uint32_t mipLevels, uint32_t arrayLayers)
{
    return mipLevel + arrayLayer * mipLevels + aspectIndex * mipLevels * arrayLayers;
}

static inline MTLTextureType _GetMetalType(bool isCubeCompatible, uint32_t neutraltype, NSUInteger arrayLength);

static inline MTLPixelFormat _GetMetalFormat(uint32_t neutralformat);

struct TextureLoader_SpecificHeader TextureLoader_ToSpecificHeader(struct TextureLoader_NeutralHeader const *neutral_texture_header)
{
    struct TextureLoader_SpecificHeader specific_texture_header;

    specific_texture_header.textureType = _GetMetalType(neutral_texture_header->isCubeMap, neutral_texture_header->type, neutral_texture_header->arrayLayers);
    specific_texture_header.pixelFormat = _GetMetalFormat(neutral_texture_header->format);
    specific_texture_header.width = neutral_texture_header->width;
    specific_texture_header.height = neutral_texture_header->height;
    specific_texture_header.depth = neutral_texture_header->depth;
    specific_texture_header.mipmapLevelCount = neutral_texture_header->mipLevels;
    assert((!neutral_texture_header->isCubeMap) || ((neutral_texture_header->type == TEXTURE_LOADER_TYPE_2D) && ((neutral_texture_header->arrayLayers % 6) == 0)));
    specific_texture_header.arrayLength = (!neutral_texture_header->isCubeMap) ? neutral_texture_header->arrayLayers : (neutral_texture_header->arrayLayers / 6);

    return specific_texture_header;
}

//--------------------------------------------------------------------------------------
static inline MTLTextureType _GetMetalType(bool isCubeCompatible, uint32_t neutraltype, NSUInteger arrayLength)
{
    if (neutraltype == TEXTURE_LOADER_TYPE_2D)
    {
        if (!isCubeCompatible)
        {
            if (arrayLength == 1)
            {
                return MTLTextureType2D;
            }
            else if (arrayLength > 1)
            {
                return MTLTextureType2DArray;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            if (arrayLength == 1)
            {
                return MTLTextureTypeCube;
            }
            else if (arrayLength > 1)
            {
                return MTLTextureTypeCubeArray;
            }
            else
            {
                return -1;
            }
        }
    }
    else if (neutraltype == TEXTURE_LOADER_TYPE_1D)
    {
        if (arrayLength == 1)
        {
            return MTLTextureType1D;
        }
        else if (arrayLength > 1)
        {
            return MTLTextureType1DArray;
        }
        else
        {
            return -1;
        }
    }
    else if (neutraltype == TEXTURE_LOADER_TYPE_3D)
    {
        if (arrayLength == 1)
        {
            return MTLTextureType3D;
        }
        else if (arrayLength > 1)
        {
            return -1;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

//--------------------------------------------------------------------------------------
static MTLPixelFormat gNeutralToMetalFormatMap[] = {
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R4G4_UNORM_PACK8
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R4G4B4A4_UNORM_PACK16
    MTLPixelFormatABGR4Unorm,            //TEXTURE_LOADER_FORMAT_B4G4R4A4_UNORM_PACK16
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R5G6B5_UNORM_PACK16
    MTLPixelFormatB5G6R5Unorm,           //TEXTURE_LOADER_FORMAT_B5G6R5_UNORM_PACK16
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R5G5B5A1_UNORM_PACK16
    MTLPixelFormatBGR5A1Unorm,           //TEXTURE_LOADER_FORMAT_B5G5R5A1_UNORM_PACK16
    MTLPixelFormatA1BGR5Unorm,           //TEXTURE_LOADER_FORMAT_A1R5G5B5_UNORM_PACK16
    MTLPixelFormatR8Unorm,               //TEXTURE_LOADER_FORMAT_R8_UNORM
    MTLPixelFormatR8Snorm,               //TEXTURE_LOADER_FORMAT_R8_SNORM
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R8_USCALED
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R8_SSCALED
    MTLPixelFormatR8Uint,                //TEXTURE_LOADER_FORMAT_R8_UINT
    MTLPixelFormatR8Sint,                //TEXTURE_LOADER_FORMAT_R8_SINT
    MTLPixelFormatR8Unorm_sRGB,          //TEXTURE_LOADER_FORMAT_R8_SRGB
    MTLPixelFormatRG8Unorm,              //TEXTURE_LOADER_FORMAT_R8G8_UNORM
    MTLPixelFormatRG8Snorm,              //TEXTURE_LOADER_FORMAT_R8G8_SNORM
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R8G8_USCALED
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R8G8_SSCALED
    MTLPixelFormatRG8Uint,               //TEXTURE_LOADER_FORMAT_R8G8_UINT
    MTLPixelFormatRG8Sint,               //TEXTURE_LOADER_FORMAT_R8G8_SINT
    MTLPixelFormatRG8Unorm_sRGB,         //TEXTURE_LOADER_FORMAT_R8G8_SRGB
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R8G8B8_UNORM
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R8G8B8_SNORM
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R8G8B8_USCALED
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R8G8B8_SSCALED
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R8G8B8_UINT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R8G8B8_SINT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R8G8B8_SRGB
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_B8G8R8_UNORM
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_B8G8R8_SNORM
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_B8G8R8_USCALED
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_B8G8R8_SSCALED
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_B8G8R8_UINT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_B8G8R8_SINT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_B8G8R8_SRGB
    MTLPixelFormatRGBA8Unorm,            //TEXTURE_LOADER_FORMAT_R8G8B8A8_UNORM
    MTLPixelFormatRGBA8Snorm,            //TEXTURE_LOADER_FORMAT_R8G8B8A8_SNORM
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R8G8B8A8_USCALED
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R8G8B8A8_SSCALED
    MTLPixelFormatRGBA8Uint,             //TEXTURE_LOADER_FORMAT_R8G8B8A8_UINT
    MTLPixelFormatRGBA8Sint,             //TEXTURE_LOADER_FORMAT_R8G8B8A8_SINT
    MTLPixelFormatRGBA8Unorm_sRGB,       //TEXTURE_LOADER_FORMAT_R8G8B8A8_SRGB
    MTLPixelFormatBGRA8Unorm,            //TEXTURE_LOADER_FORMAT_B8G8R8A8_UNORM
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_B8G8R8A8_SNORM
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_B8G8R8A8_USCALED
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_B8G8R8A8_SSCALED
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_B8G8R8A8_UINT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_B8G8R8A8_SINT
    MTLPixelFormatBGRA8Unorm_sRGB,       //TEXTURE_LOADER_FORMAT_B8G8R8A8_SRGB
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_A8B8G8R8_UNORM_PACK32
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_A8B8G8R8_SNORM_PACK32
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_A8B8G8R8_USCALED_PACK32
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_A8B8G8R8_SSCALED_PACK32
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_A8B8G8R8_UINT_PACK32
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_A8B8G8R8_SINT_PACK32
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_A8B8G8R8_SRGB_PACK32
    MTLPixelFormatRGB10A2Unorm,          //TEXTURE_LOADER_FORMAT_A2R10G10B10_UNORM_PACK32
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_A2R10G10B10_SNORM_PACK32
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_A2R10G10B10_USCALED_PACK32
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_A2R10G10B10_SSCALED_PACK32
    MTLPixelFormatRGB10A2Uint,           //TEXTURE_LOADER_FORMAT_A2R10G10B10_UINT_PACK32
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_A2R10G10B10_SINT_PACK32
    MTLPixelFormatBGR10A2Unorm,          //TEXTURE_LOADER_FORMAT_A2B10G10R10_UNORM_PACK32
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_A2B10G10R10_SNORM_PACK32
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_A2B10G10R10_USCALED_PACK32
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_A2B10G10R10_SSCALED_PACK32
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_A2B10G10R10_UINT_PACK32
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_A2B10G10R10_SINT_PACK32
    MTLPixelFormatR16Unorm,              //TEXTURE_LOADER_FORMAT_R16_UNORM
    MTLPixelFormatR16Snorm,              //TEXTURE_LOADER_FORMAT_R16_SNORM
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R16_USCALED
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R16_SSCALED
    MTLPixelFormatR16Uint,               //TEXTURE_LOADER_FORMAT_R16_UINT
    MTLPixelFormatR16Sint,               //TEXTURE_LOADER_FORMAT_R16_SINT
    MTLPixelFormatR16Float,              //TEXTURE_LOADER_FORMAT_R16_SFLOAT
    MTLPixelFormatRG16Unorm,             //TEXTURE_LOADER_FORMAT_R16G16_UNORM
    MTLPixelFormatRG16Snorm,             //TEXTURE_LOADER_FORMAT_R16G16_SNORM
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R16G16_USCALED
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R16G16_SSCALED
    MTLPixelFormatRG16Uint,              //TEXTURE_LOADER_FORMAT_R16G16_UINT
    MTLPixelFormatRG16Sint,              //TEXTURE_LOADER_FORMAT_R16G16_SINT
    MTLPixelFormatRG16Float,             //TEXTURE_LOADER_FORMAT_R16G16_SFLOAT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R16G16B16_UNORM
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R16G16B16_SNORM
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R16G16B16_USCALED
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R16G16B16_SSCALED
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R16G16B16_UINT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R16G16B16_SINT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R16G16B16_SFLOAT
    MTLPixelFormatRGBA16Unorm,           //TEXTURE_LOADER_FORMAT_R16G16B16A16_UNORM
    MTLPixelFormatRGBA16Snorm,           //TEXTURE_LOADER_FORMAT_R16G16B16A16_SNORM
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R16G16B16A16_USCALED
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R16G16B16A16_SSCALED
    MTLPixelFormatRGBA16Uint,            //TEXTURE_LOADER_FORMAT_R16G16B16A16_UINT
    MTLPixelFormatRGBA16Sint,            //TEXTURE_LOADER_FORMAT_R16G16B16A16_SINT
    MTLPixelFormatRGBA16Float,           //TEXTURE_LOADER_FORMAT_R16G16B16A16_SFLOAT
    MTLPixelFormatR32Uint,               //TEXTURE_LOADER_FORMAT_R32_UINT
    MTLPixelFormatR32Sint,               //TEXTURE_LOADER_FORMAT_R32_SINT
    MTLPixelFormatR32Float,              //TEXTURE_LOADER_FORMAT_R32_SFLOAT
    MTLPixelFormatRG32Uint,              //TEXTURE_LOADER_FORMAT_R32G32_UINT
    MTLPixelFormatRG32Sint,              //TEXTURE_LOADER_FORMAT_R32G32_SINT
    MTLPixelFormatRG32Float,             //TEXTURE_LOADER_FORMAT_R32G32_SFLOAT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R32G32B32_UINT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R32G32B32_SINT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R32G32B32_SFLOAT
    MTLPixelFormatRGBA32Uint,            //TEXTURE_LOADER_FORMAT_R32G32B32A32_UINT
    MTLPixelFormatRGBA32Sint,            //TEXTURE_LOADER_FORMAT_R32G32B32A32_SINT
    MTLPixelFormatRGBA32Float,           //TEXTURE_LOADER_FORMAT_R32G32B32A32_SFLOAT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R64_UINT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R64_SINT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R64_SFLOAT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R64G64_UINT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R64G64_SINT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R64G64_SFLOAT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R64G64B64_UINT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R64G64B64_SINT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R64G64B64_SFLOAT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R64G64B64A64_UINT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R64G64B64A64_SINT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_R64G64B64A64_SFLOAT
    MTLPixelFormatRG11B10Float,          //TEXTURE_LOADER_FORMAT_B10G11R11_UFLOAT_PACK32
    MTLPixelFormatRGB9E5Float,           //TEXTURE_LOADER_FORMAT_E5B9G9R9_UFLOAT_PACK32
    MTLPixelFormatDepth16Unorm,          //TEXTURE_LOADER_FORMAT_D16_UNORM
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_X8_D24_UNORM_PACK32
    MTLPixelFormatDepth32Float,          //TEXTURE_LOADER_FORMAT_D32_SFLOAT
    MTLPixelFormatStencil8,              //TEXTURE_LOADER_FORMAT_S8_UINT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_D16_UNORM_S8_UINT
    MTLPixelFormatDepth24Unorm_Stencil8, //TEXTURE_LOADER_FORMAT_D24_UNORM_S8_UINT
    MTLPixelFormatDepth32Float_Stencil8, //TEXTURE_LOADER_FORMAT_D32_SFLOAT_S8_UINT
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_BC1_RGB_UNORM_BLOCK
    MTLPixelFormatInvalid,               //TEXTURE_LOADER_FORMAT_BC1_RGB_SRGB_BLOCK
    MTLPixelFormatBC1_RGBA,              //TEXTURE_LOADER_FORMAT_BC1_RGBA_UNORM_BLOCK
    MTLPixelFormatBC1_RGBA_sRGB,         //TEXTURE_LOADER_FORMAT_BC1_RGBA_SRGB_BLOCK
    MTLPixelFormatBC2_RGBA,              //TEXTURE_LOADER_FORMAT_BC2_UNORM_BLOCK
    MTLPixelFormatBC2_RGBA_sRGB,         //TEXTURE_LOADER_FORMAT_BC2_SRGB_BLOCK
    MTLPixelFormatBC3_RGBA,              //TEXTURE_LOADER_FORMAT_BC3_UNORM_BLOCK
    MTLPixelFormatBC3_RGBA_sRGB,         //TEXTURE_LOADER_FORMAT_BC3_SRGB_BLOCK
    MTLPixelFormatBC4_RUnorm,            //TEXTURE_LOADER_FORMAT_BC4_UNORM_BLOCK
    MTLPixelFormatBC4_RSnorm,            //TEXTURE_LOADER_FORMAT_BC4_SNORM_BLOCK
    MTLPixelFormatBC5_RGUnorm,           //TEXTURE_LOADER_FORMAT_BC5_UNORM_BLOCK
    MTLPixelFormatBC5_RGSnorm,           //TEXTURE_LOADER_FORMAT_BC5_SNORM_BLOCK
    MTLPixelFormatBC6H_RGBFloat,         //TEXTURE_LOADER_FORMAT_BC6H_UFLOAT_BLOCK
    MTLPixelFormatBC6H_RGBUfloat,        //TEXTURE_LOADER_FORMAT_BC6H_SFLOAT_BLOCK
    MTLPixelFormatBC7_RGBAUnorm,         //TEXTURE_LOADER_FORMAT_BC7_UNORM_BLOCK
    MTLPixelFormatBC7_RGBAUnorm_sRGB,    //TEXTURE_LOADER_FORMAT_BC7_SRGB_BLOCK
    MTLPixelFormatETC2_RGB8,             //TEXTURE_LOADER_FORMAT_ETC2_R8G8B8_UNORM_BLOCK
    MTLPixelFormatETC2_RGB8_sRGB,        //TEXTURE_LOADER_FORMAT_ETC2_R8G8B8_SRGB_BLOCK
    MTLPixelFormatETC2_RGB8A1,           //TEXTURE_LOADER_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK
    MTLPixelFormatETC2_RGB8A1_sRGB,      //TEXTURE_LOADER_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK
    MTLPixelFormatETC2_RGB8,             //TEXTURE_LOADER_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK
    MTLPixelFormatETC2_RGB8_sRGB,        //TEXTURE_LOADER_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK
    MTLPixelFormatEAC_R11Unorm,          //TEXTURE_LOADER_FORMAT_EAC_R11_UNORM_BLOCK
    MTLPixelFormatEAC_R11Snorm,          //TEXTURE_LOADER_FORMAT_EAC_R11_SNORM_BLOCK
    MTLPixelFormatEAC_RG11Unorm,         //TEXTURE_LOADER_FORMAT_EAC_R11G11_UNORM_BLOCK
    MTLPixelFormatEAC_RG11Snorm,         //TEXTURE_LOADER_FORMAT_EAC_R11G11_SNORM_BLOCK
    MTLPixelFormatASTC_4x4_LDR,          //TEXTURE_LOADER_FORMAT_ASTC_4x4_UNORM_BLOCK
    MTLPixelFormatASTC_4x4_sRGB,         //TEXTURE_LOADER_FORMAT_ASTC_4x4_SRGB_BLOCK
    MTLPixelFormatASTC_5x4_LDR,          //TEXTURE_LOADER_FORMAT_ASTC_5x4_UNORM_BLOCK
    MTLPixelFormatASTC_5x4_sRGB,         //TEXTURE_LOADER_FORMAT_ASTC_5x4_SRGB_BLOCK
    MTLPixelFormatASTC_5x5_LDR,          //TEXTURE_LOADER_FORMAT_ASTC_5x5_UNORM_BLOCK
    MTLPixelFormatASTC_5x5_sRGB,         //TEXTURE_LOADER_FORMAT_ASTC_5x5_SRGB_BLOCK
    MTLPixelFormatASTC_6x5_LDR,          //TEXTURE_LOADER_FORMAT_ASTC_6x5_UNORM_BLOCK
    MTLPixelFormatASTC_6x5_sRGB,         //TEXTURE_LOADER_FORMAT_ASTC_6x5_SRGB_BLOCK
    MTLPixelFormatASTC_6x6_LDR,          //TEXTURE_LOADER_FORMAT_ASTC_6x6_UNORM_BLOCK
    MTLPixelFormatASTC_6x6_sRGB,         //TEXTURE_LOADER_FORMAT_ASTC_6x6_SRGB_BLOCK
    MTLPixelFormatASTC_8x5_LDR,          //TEXTURE_LOADER_FORMAT_ASTC_8x5_UNORM_BLOCK
    MTLPixelFormatASTC_8x5_sRGB,         //TEXTURE_LOADER_FORMAT_ASTC_8x5_SRGB_BLOCK
    MTLPixelFormatASTC_8x6_LDR,          //TEXTURE_LOADER_FORMAT_ASTC_8x6_UNORM_BLOCK
    MTLPixelFormatASTC_8x6_sRGB,         //TEXTURE_LOADER_FORMAT_ASTC_8x6_SRGB_BLOCK
    MTLPixelFormatASTC_8x8_LDR,          //TEXTURE_LOADER_FORMAT_ASTC_8x8_UNORM_BLOCK
    MTLPixelFormatASTC_8x8_sRGB,         //TEXTURE_LOADER_FORMAT_ASTC_8x8_SRGB_BLOCK
    MTLPixelFormatASTC_10x5_LDR,         //TEXTURE_LOADER_FORMAT_ASTC_10x5_UNORM_BLOCK
    MTLPixelFormatASTC_10x5_sRGB,        //TEXTURE_LOADER_FORMAT_ASTC_10x5_SRGB_BLOCK
    MTLPixelFormatASTC_10x6_LDR,         //TEXTURE_LOADER_FORMAT_ASTC_10x6_UNORM_BLOCK
    MTLPixelFormatASTC_10x6_sRGB,        //TEXTURE_LOADER_FORMAT_ASTC_10x6_SRGB_BLOCK
    MTLPixelFormatASTC_10x8_LDR,         //TEXTURE_LOADER_FORMAT_ASTC_10x8_UNORM_BLOCK
    MTLPixelFormatASTC_10x8_sRGB,        //TEXTURE_LOADER_FORMAT_ASTC_10x8_SRGB_BLOCK
    MTLPixelFormatASTC_10x10_LDR,        //TEXTURE_LOADER_FORMAT_ASTC_10x10_UNORM_BLOCK
    MTLPixelFormatASTC_10x10_sRGB,       //TEXTURE_LOADER_FORMAT_ASTC_10x10_SRGB_BLOCK
    MTLPixelFormatASTC_12x10_LDR,        //TEXTURE_LOADER_FORMAT_ASTC_12x10_UNORM_BLOCK
    MTLPixelFormatASTC_12x10_sRGB,       //TEXTURE_LOADER_FORMAT_ASTC_12x10_SRGB_BLOCK
    MTLPixelFormatASTC_12x12_LDR,        //TEXTURE_LOADER_FORMAT_ASTC_12x12_UNORM_BLOCK
    MTLPixelFormatASTC_12x12_sRGB,       //TEXTURE_LOADER_FORMAT_ASTC_12x12_SRGB_BLOCK
};
static_assert(TEXTURE_LOADER_FORMAT_RANGE_SIZE == (sizeof(gNeutralToMetalFormatMap) / sizeof(gNeutralToMetalFormatMap[0])), "gNeutralToMetalFormatMap may not match!");
static inline MTLPixelFormat _GetMetalFormat(uint32_t neutralformat)
{
    assert(neutralformat < (sizeof(gNeutralToMetalFormatMap) / sizeof(gNeutralToMetalFormatMap[0])));
    return gNeutralToMetalFormatMap[neutralformat];
}
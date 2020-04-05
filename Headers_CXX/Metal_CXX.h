#ifndef _METAL_CXX_H_
#define _METAL_CXX_H_ 1

#include "NSRuntime_CXX.h"

extern "C" struct MTLDevice *MTLCreateSystemDefaultDevice(void);

typedef NSUInteger MTLPixelFormat;
enum
{
    MTLPixelFormatInvalid = 0,

    /* Normal 8 bit formats */

    MTLPixelFormatA8Unorm = 1,

    MTLPixelFormatR8Unorm = 10,
    MTLPixelFormatR8Unorm_sRGB = 11,

    MTLPixelFormatR8Snorm = 12,
    MTLPixelFormatR8Uint = 13,
    MTLPixelFormatR8Sint = 14,

    /* Normal 16 bit formats */

    MTLPixelFormatR16Unorm = 20,
    MTLPixelFormatR16Snorm = 22,
    MTLPixelFormatR16Uint = 23,
    MTLPixelFormatR16Sint = 24,
    MTLPixelFormatR16Float = 25,

    MTLPixelFormatRG8Unorm = 30,
    MTLPixelFormatRG8Unorm_sRGB = 31,
    MTLPixelFormatRG8Snorm = 32,
    MTLPixelFormatRG8Uint = 33,
    MTLPixelFormatRG8Sint = 34,

    /* Packed 16 bit formats */

    MTLPixelFormatB5G6R5Unorm = 40,
    MTLPixelFormatA1BGR5Unorm = 41,
    MTLPixelFormatABGR4Unorm = 42,
    MTLPixelFormatBGR5A1Unorm = 43,

    /* Normal 32 bit formats */

    MTLPixelFormatR32Uint = 53,
    MTLPixelFormatR32Sint = 54,
    MTLPixelFormatR32Float = 55,

    MTLPixelFormatRG16Unorm = 60,
    MTLPixelFormatRG16Snorm = 62,
    MTLPixelFormatRG16Uint = 63,
    MTLPixelFormatRG16Sint = 64,
    MTLPixelFormatRG16Float = 65,

    MTLPixelFormatRGBA8Unorm = 70,
    MTLPixelFormatRGBA8Unorm_sRGB = 71,
    MTLPixelFormatRGBA8Snorm = 72,
    MTLPixelFormatRGBA8Uint = 73,
    MTLPixelFormatRGBA8Sint = 74,

    MTLPixelFormatBGRA8Unorm = 80,
    MTLPixelFormatBGRA8Unorm_sRGB = 81,

    /* Packed 32 bit formats */

    MTLPixelFormatRGB10A2Unorm = 90,
    MTLPixelFormatRGB10A2Uint = 91,

    MTLPixelFormatRG11B10Float = 92,
    MTLPixelFormatRGB9E5Float = 93,

    MTLPixelFormatBGR10A2Unorm = 94,

    MTLPixelFormatBGR10_XR = 554,
    MTLPixelFormatBGR10_XR_sRGB = 555,

    /* Normal 64 bit formats */

    MTLPixelFormatRG32Uint = 103,
    MTLPixelFormatRG32Sint = 104,
    MTLPixelFormatRG32Float = 105,

    MTLPixelFormatRGBA16Unorm = 110,
    MTLPixelFormatRGBA16Snorm = 112,
    MTLPixelFormatRGBA16Uint = 113,
    MTLPixelFormatRGBA16Sint = 114,
    MTLPixelFormatRGBA16Float = 115,

    MTLPixelFormatBGRA10_XR = 552,
    MTLPixelFormatBGRA10_XR_sRGB = 553,

    /* Normal 128 bit formats */

    MTLPixelFormatRGBA32Uint = 123,
    MTLPixelFormatRGBA32Sint = 124,
    MTLPixelFormatRGBA32Float = 125,

    /* Compressed formats. */

    /* S3TC/DXT */
    MTLPixelFormatBC1_RGBA = 130,
    MTLPixelFormatBC1_RGBA_sRGB = 131,
    MTLPixelFormatBC2_RGBA = 132,
    MTLPixelFormatBC2_RGBA_sRGB = 133,
    MTLPixelFormatBC3_RGBA = 134,
    MTLPixelFormatBC3_RGBA_sRGB = 135,

    /* RGTC */
    MTLPixelFormatBC4_RUnorm = 140,
    MTLPixelFormatBC4_RSnorm = 141,
    MTLPixelFormatBC5_RGUnorm = 142,
    MTLPixelFormatBC5_RGSnorm = 143,

    /* BPTC */
    MTLPixelFormatBC6H_RGBFloat = 150,
    MTLPixelFormatBC6H_RGBUfloat = 151,
    MTLPixelFormatBC7_RGBAUnorm = 152,
    MTLPixelFormatBC7_RGBAUnorm_sRGB = 153,

    /* PVRTC */
    MTLPixelFormatPVRTC_RGB_2BPP = 160,
    MTLPixelFormatPVRTC_RGB_2BPP_sRGB = 161,
    MTLPixelFormatPVRTC_RGB_4BPP = 162,
    MTLPixelFormatPVRTC_RGB_4BPP_sRGB = 163,
    MTLPixelFormatPVRTC_RGBA_2BPP = 164,
    MTLPixelFormatPVRTC_RGBA_2BPP_sRGB = 165,
    MTLPixelFormatPVRTC_RGBA_4BPP = 166,
    MTLPixelFormatPVRTC_RGBA_4BPP_sRGB = 167,

    /* ETC2 */
    MTLPixelFormatEAC_R11Unorm = 170,
    MTLPixelFormatEAC_R11Snorm = 172,
    MTLPixelFormatEAC_RG11Unorm = 174,
    MTLPixelFormatEAC_RG11Snorm = 176,
    MTLPixelFormatEAC_RGBA8 = 178,
    MTLPixelFormatEAC_RGBA8_sRGB = 179,

    MTLPixelFormatETC2_RGB8 = 180,
    MTLPixelFormatETC2_RGB8_sRGB = 181,
    MTLPixelFormatETC2_RGB8A1 = 182,
    MTLPixelFormatETC2_RGB8A1_sRGB = 183,

    /* ASTC */
    MTLPixelFormatASTC_4x4_sRGB = 186,
    MTLPixelFormatASTC_5x4_sRGB = 187,
    MTLPixelFormatASTC_5x5_sRGB = 188,
    MTLPixelFormatASTC_6x5_sRGB = 189,
    MTLPixelFormatASTC_6x6_sRGB = 190,
    MTLPixelFormatASTC_8x5_sRGB = 192,
    MTLPixelFormatASTC_8x6_sRGB = 193,
    MTLPixelFormatASTC_8x8_sRGB = 194,
    MTLPixelFormatASTC_10x5_sRGB = 195,
    MTLPixelFormatASTC_10x6_sRGB = 196,
    MTLPixelFormatASTC_10x8_sRGB = 197,
    MTLPixelFormatASTC_10x10_sRGB = 198,
    MTLPixelFormatASTC_12x10_sRGB = 199,
    MTLPixelFormatASTC_12x12_sRGB = 200,

    MTLPixelFormatASTC_4x4_LDR = 204,
    MTLPixelFormatASTC_5x4_LDR = 205,
    MTLPixelFormatASTC_5x5_LDR = 206,
    MTLPixelFormatASTC_6x5_LDR = 207,
    MTLPixelFormatASTC_6x6_LDR = 208,
    MTLPixelFormatASTC_8x5_LDR = 210,
    MTLPixelFormatASTC_8x6_LDR = 211,
    MTLPixelFormatASTC_8x8_LDR = 212,
    MTLPixelFormatASTC_10x5_LDR = 213,
    MTLPixelFormatASTC_10x6_LDR = 214,
    MTLPixelFormatASTC_10x8_LDR = 215,
    MTLPixelFormatASTC_10x10_LDR = 216,
    MTLPixelFormatASTC_12x10_LDR = 217,
    MTLPixelFormatASTC_12x12_LDR = 218,

    /*!
     @constant MTLPixelFormatGBGR422
     @abstract A pixel format where the red and green channels are subsampled horizontally.  Two pixels are stored in 32 bits, with shared red and blue values, and unique green values.
     @discussion This format is equivalent to YUY2, YUYV, yuvs, or GL_RGB_422_APPLE/GL_UNSIGNED_SHORT_8_8_REV_APPLE.   The component order, from lowest addressed byte to highest, is Y0, Cb, Y1, Cr.  There is no implicit colorspace conversion from YUV to RGB, the shader will receive (Cr, Y, Cb, 1).  422 textures must have a width that is a multiple of 2, and can only be used for 2D non-mipmap textures.  When sampling, ClampToEdge is the only usable wrap mode.
     */
    MTLPixelFormatGBGR422 = 240,

    /*!
     @constant MTLPixelFormatBGRG422
     @abstract A pixel format where the red and green channels are subsampled horizontally.  Two pixels are stored in 32 bits, with shared red and blue values, and unique green values.
     @discussion This format is equivalent to UYVY, 2vuy, or GL_RGB_422_APPLE/GL_UNSIGNED_SHORT_8_8_APPLE. The component order, from lowest addressed byte to highest, is Cb, Y0, Cr, Y1.  There is no implicit colorspace conversion from YUV to RGB, the shader will receive (Cr, Y, Cb, 1).  422 textures must have a width that is a multiple of 2, and can only be used for 2D non-mipmap textures.  When sampling, ClampToEdge is the only usable wrap mode.
     */
    MTLPixelFormatBGRG422 = 241,

    /* Depth */

    MTLPixelFormatDepth16Unorm = 250,
    MTLPixelFormatDepth32Float = 252,

    /* Stencil */

    MTLPixelFormatStencil8 = 253,

    /* Depth Stencil */

    MTLPixelFormatDepth24Unorm_Stencil8 = 255,
    MTLPixelFormatDepth32Float_Stencil8 = 260,

    MTLPixelFormatX32_Stencil8 = 261,
    MTLPixelFormatX24_Stencil8 = 262,
};

typedef NSUInteger MTLVertexStepFunction;
enum
{
    MTLVertexStepFunctionConstant = 0,
    MTLVertexStepFunctionPerVertex = 1,
    MTLVertexStepFunctionPerInstance = 2,
    MTLVertexStepFunctionPerPatch = 3,
    MTLVertexStepFunctionPerPatchControlPoint = 4
};

typedef NSUInteger MTLVertexFormat;
enum
{
    MTLVertexFormatInvalid = 0,

    MTLVertexFormatUChar2 = 1,
    MTLVertexFormatUChar3 = 2,
    MTLVertexFormatUChar4 = 3,

    MTLVertexFormatChar2 = 4,
    MTLVertexFormatChar3 = 5,
    MTLVertexFormatChar4 = 6,

    MTLVertexFormatUChar2Normalized = 7,
    MTLVertexFormatUChar3Normalized = 8,
    MTLVertexFormatUChar4Normalized = 9,

    MTLVertexFormatChar2Normalized = 10,
    MTLVertexFormatChar3Normalized = 11,
    MTLVertexFormatChar4Normalized = 12,

    MTLVertexFormatUShort2 = 13,
    MTLVertexFormatUShort3 = 14,
    MTLVertexFormatUShort4 = 15,

    MTLVertexFormatShort2 = 16,
    MTLVertexFormatShort3 = 17,
    MTLVertexFormatShort4 = 18,

    MTLVertexFormatUShort2Normalized = 19,
    MTLVertexFormatUShort3Normalized = 20,
    MTLVertexFormatUShort4Normalized = 21,

    MTLVertexFormatShort2Normalized = 22,
    MTLVertexFormatShort3Normalized = 23,
    MTLVertexFormatShort4Normalized = 24,

    MTLVertexFormatHalf2 = 25,
    MTLVertexFormatHalf3 = 26,
    MTLVertexFormatHalf4 = 27,

    MTLVertexFormatFloat = 28,
    MTLVertexFormatFloat2 = 29,
    MTLVertexFormatFloat3 = 30,
    MTLVertexFormatFloat4 = 31,

    MTLVertexFormatInt = 32,
    MTLVertexFormatInt2 = 33,
    MTLVertexFormatInt3 = 34,
    MTLVertexFormatInt4 = 35,

    MTLVertexFormatUInt = 36,
    MTLVertexFormatUInt2 = 37,
    MTLVertexFormatUInt3 = 38,
    MTLVertexFormatUInt4 = 39,

    MTLVertexFormatInt1010102Normalized = 40,
    MTLVertexFormatUInt1010102Normalized = 41,

    MTLVertexFormatUChar4Normalized_BGRA = 42,

    MTLVertexFormatUChar = 45,
    MTLVertexFormatChar = 46,
    MTLVertexFormatUCharNormalized = 47,
    MTLVertexFormatCharNormalized = 48,

    MTLVertexFormatUShort = 49,
    MTLVertexFormatShort = 50,
    MTLVertexFormatUShortNormalized = 51,
    MTLVertexFormatShortNormalized = 52,

    MTLVertexFormatHalf = 53
};

struct MTLVertexDescriptor *MTLVertexDescriptor_alloc();
struct MTLVertexDescriptor *MTLVertexDescriptor_init(struct MTLVertexDescriptor *self);
struct MTLVertexBufferLayoutDescriptorArray *MTLVertexDescriptor_layouts(struct MTLVertexDescriptor *self);
struct MTLVertexBufferLayoutDescriptor *MTLVertexBufferLayoutDescriptorArray_objectAtIndexedSubscript(struct MTLVertexBufferLayoutDescriptorArray *self, NSUInteger index);
void MTLVertexBufferLayoutDescriptor_setStride(struct MTLVertexBufferLayoutDescriptor *self, NSUInteger stride);
void MTLVertexBufferLayoutDescriptor_setStepFunction(struct MTLVertexBufferLayoutDescriptor *self, MTLVertexStepFunction stepFunction);
void MTLVertexBufferLayoutDescriptor_setStepRate(struct MTLVertexBufferLayoutDescriptor *self, NSUInteger stepRate);
struct MTLVertexAttributeDescriptorArray *MTLVertexDescriptor_attributes(struct MTLVertexDescriptor *self);
struct MTLVertexAttributeDescriptor *MTLVertexAttributeDescriptorArray_objectAtIndexedSubscript(struct MTLVertexAttributeDescriptorArray *self, NSUInteger index);
void MTLVertexAttributeDescriptor_setFormat(struct MTLVertexAttributeDescriptor *self, MTLVertexFormat format);
void MTLVertexAttributeDescriptor_setOffset(struct MTLVertexAttributeDescriptor *self, NSUInteger offset);
void MTLVertexAttributeDescriptor_setBufferIndex(struct MTLVertexAttributeDescriptor *self, NSUInteger bufferIndex);
static inline struct MTLVertexBufferLayoutDescriptor *MTLVertexDescriptor_layoutAt(struct MTLVertexDescriptor *self, NSUInteger index)
{
    return MTLVertexBufferLayoutDescriptorArray_objectAtIndexedSubscript(MTLVertexDescriptor_layouts(self), index);
}
static inline struct MTLVertexAttributeDescriptor *MTLVertexDescriptor_attributeAt(struct MTLVertexDescriptor *self, NSUInteger index)
{
    return MTLVertexAttributeDescriptorArray_objectAtIndexedSubscript(MTLVertexDescriptor_attributes(self), index);
}

struct MTLRenderPipelineDescriptor *MTLRenderPipelineDescriptor_alloc();
struct MTLRenderPipelineDescriptor *MTLRenderPipelineDescriptor_init(struct MTLRenderPipelineDescriptor *self);
void MTLRenderPipelineDescriptor_setLabel(struct MTLRenderPipelineDescriptor *self, struct NSString *label);
void MTLRenderPipelineDescriptor_setVertexFunction(struct MTLRenderPipelineDescriptor *self, struct MTLFunction *vertexFunction);
void MTLRenderPipelineDescriptor_setFragmentFunction(struct MTLRenderPipelineDescriptor *self, struct MTLFunction *fragmentFunction);
void MTLRenderPipelineDescriptor_setVertexDescriptor(struct MTLRenderPipelineDescriptor *self, struct MTLVertexDescriptor *vertexDescriptor);
void MTLRenderPipelineDescriptor_setSampleCount(struct MTLRenderPipelineDescriptor *self, NSUInteger sampleCount);
struct MTLRenderPipelineColorAttachmentDescriptorArray *MTLRenderPipelineDescriptor_colorAttachments(struct MTLRenderPipelineDescriptor *self);
struct MTLRenderPipelineColorAttachmentDescriptor *MTLRenderPipelineColorAttachmentDescriptorArray_objectAtIndexedSubscript(struct MTLRenderPipelineColorAttachmentDescriptorArray *self, NSUInteger attachmentIndex);
void MTLRenderPipelineColorAttachmentDescriptor_setPixelFormat(struct MTLRenderPipelineColorAttachmentDescriptor *self, MTLPixelFormat pixelFormat);
void MTLRenderPipelineDescriptor_setDepthAttachmentPixelFormat(struct MTLRenderPipelineDescriptor *self, MTLPixelFormat pixelFormat);
void MTLRenderPipelineDescriptor_setStencilAttachmentPixelFormat(struct MTLRenderPipelineDescriptor *self, MTLPixelFormat pixelFormat);
void MTLRenderPipelineDescriptor_release(struct MTLRenderPipelineDescriptor *self);
NSUInteger MTLRenderPipelineDescriptor_retainCount(struct MTLRenderPipelineDescriptor *self);
static inline struct MTLRenderPipelineColorAttachmentDescriptor *MTLRenderPipelineDescriptor_colorAttachmentAt(struct MTLRenderPipelineDescriptor *self, NSUInteger attachmentIndex)
{
    return MTLRenderPipelineColorAttachmentDescriptorArray_objectAtIndexedSubscript(MTLRenderPipelineDescriptor_colorAttachments(self), attachmentIndex);
}

struct MTLLibrary *MTLDevice_newDefaultLibrary(struct MTLDevice *self);
struct MTLFunction *MTLLibrary_newFunctionWithName(struct MTLLibrary *self, struct NSString *functionName);
void MTLFunction_release(struct MTLFunction *self);
NSUInteger MTLFunction_retainCount(struct MTLFunction *self);

#endif
#include <stddef.h>

#include "Headers_CXX/MetalKit_CXX.h"

struct MTLDevice *g_device = NULL;
struct MTKView *g_view;

void _I_Renderer_drawableSizeWillChange_(struct NSApplicationDelegate *, struct MTKViewDelegate_drawableSizeWillChange_ *, struct MTKView *view, CGSize size)
{
}

void _I_Renderer_drawInMTKView_(struct NSApplicationDelegate *, struct MTKViewDelegate_drawInMTKView_ *, struct MTKView *view)
{
}

#include "ShaderTypes.h"

void demo_init()
{
    struct MTLVertexDescriptor *vertexdescriptor = MTLVertexDescriptor_init(MTLVertexDescriptor_alloc());

    struct MTLVertexBufferLayoutDescriptor *layout_tmp = MTLVertexDescriptor_layoutAt(vertexdescriptor, BufferIndexMeshPositions);
    MTLVertexBufferLayoutDescriptor_setStride(layout_tmp, 12);
    MTLVertexBufferLayoutDescriptor_setStepFunction(layout_tmp, MTLVertexStepFunctionPerVertex);
    MTLVertexBufferLayoutDescriptor_setStepRate(layout_tmp, 1);

    layout_tmp = MTLVertexDescriptor_layoutAt(vertexdescriptor, BufferIndexMeshGenerics);
    MTLVertexBufferLayoutDescriptor_setStride(layout_tmp, 8);
    MTLVertexBufferLayoutDescriptor_setStepFunction(layout_tmp, MTLVertexStepFunctionPerVertex);
    MTLVertexBufferLayoutDescriptor_setStepRate(layout_tmp, 1);

    struct MTLVertexAttributeDescriptor *attribute_tmp = MTLVertexDescriptor_attributeAt(vertexdescriptor, VertexAttributePosition);
    MTLVertexAttributeDescriptor_setFormat(attribute_tmp, MTLVertexFormatFloat3);
    MTLVertexAttributeDescriptor_setOffset(attribute_tmp, 0);
    MTLVertexAttributeDescriptor_setBufferIndex(attribute_tmp, BufferIndexMeshPositions);

    attribute_tmp = MTLVertexDescriptor_attributeAt(vertexdescriptor, VertexAttributeTexcoord);
    MTLVertexAttributeDescriptor_setFormat(attribute_tmp, MTLVertexFormatFloat2);
    MTLVertexAttributeDescriptor_setOffset(attribute_tmp, 0);
    MTLVertexAttributeDescriptor_setBufferIndex(attribute_tmp, BufferIndexMeshGenerics);

    struct MTLLibrary *defaultLibrary = MTLDevice_newDefaultLibrary(g_device);

    struct NSString *string_tmp = NSString_stringWithUTF8String("vertexShader");
    struct MTLFunction *vertexFunction = MTLLibrary_newFunctionWithName(defaultLibrary, string_tmp);
    NSString_release(string_tmp);

    string_tmp = NSString_stringWithUTF8String("fragmentShader");
    struct MTLFunction *fragmentFunction = MTLLibrary_newFunctionWithName(defaultLibrary, string_tmp);
    NSString_release(string_tmp);

    struct MTLRenderPipelineDescriptor *pipelineStateDescriptor = MTLRenderPipelineDescriptor_init(MTLRenderPipelineDescriptor_alloc());
    MTLRenderPipelineDescriptor_setVertexFunction(pipelineStateDescriptor, vertexFunction);
    MTLRenderPipelineDescriptor_setFragmentFunction(pipelineStateDescriptor, fragmentFunction);
    MTLRenderPipelineDescriptor_setVertexDescriptor(pipelineStateDescriptor, vertexdescriptor);
    MTLRenderPipelineDescriptor_setSampleCount(pipelineStateDescriptor, 1);
    MTLRenderPipelineColorAttachmentDescriptor_setPixelFormat(MTLRenderPipelineDescriptor_colorAttachmentAt(pipelineStateDescriptor, 0), MTLPixelFormatBGRA8Unorm_sRGB);
    MTLRenderPipelineDescriptor_setDepthAttachmentPixelFormat(pipelineStateDescriptor, MTLPixelFormatDepth32Float_Stencil8);
    MTLRenderPipelineDescriptor_setStencilAttachmentPixelFormat(pipelineStateDescriptor, MTLPixelFormatDepth32Float_Stencil8);
    MTLFunction_release(vertexFunction);
    MTLFunction_release(fragmentFunction);
    MTLVertexDescriptor_release(vertexdescriptor);

    struct NSError *error = (struct NSError *)(1);
    struct MTLRenderPipelineState *pipelineState = MTLDevice_newRenderPipelineStateWithDescriptor(g_device, pipelineStateDescriptor, &error);
    MTLRenderPipelineDescriptor_release(pipelineStateDescriptor);

    
}

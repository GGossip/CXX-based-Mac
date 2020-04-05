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

    MTLVertexDescriptor_layoutAt(vertexdescriptor, BufferIndexMeshPositions, 12, MTLVertexStepFunctionPerVertex, 1);
    MTLVertexDescriptor_layoutAt(vertexdescriptor, BufferIndexMeshGenerics, 0, MTLVertexStepFunctionPerVertex, 1);

    MTLVertexDescriptor_attributeAt(vertexdescriptor, VertexAttributePosition, MTLVertexFormatFloat3, 0, BufferIndexMeshPositions);
    MTLVertexDescriptor_attributeAt(vertexdescriptor, VertexAttributePosition, MTLVertexFormatFloat2, 0, BufferIndexMeshGenerics);

    struct MTLLibrary *defaultLibrary = MTLDevice_newDefaultLibrary(g_device);

    struct NSString *string_tmp = NSString_stringWithUTF8String("vertexShader");
    struct MTLFunction *vertexFunction = MTLLibrary_newFunctionWithName(defaultLibrary, string_tmp);
    NSString_release(string_tmp);

    string_tmp = NSString_stringWithUTF8String("fragmentShader");
    struct MTLFunction *fragmentFunction = MTLLibrary_newFunctionWithName(defaultLibrary, string_tmp);
    NSString_release(string_tmp);
}

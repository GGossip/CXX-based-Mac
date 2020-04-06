#include <stddef.h>

#include "Headers_CXX/MetalKit_CXX.h"

static void demo_resize(struct MTKView *view, CGSize size);
static void demo_draw(struct MTKView *view);

void _I_Renderer_drawableSizeWillChange_(struct NSApplicationDelegate *, struct MTKViewDelegate_drawableSizeWillChange_ *, struct MTKView *view, CGSize size)
{
    demo_resize(view, size);
}

void _I_Renderer_drawInMTKView_(struct NSApplicationDelegate *, struct MTKViewDelegate_drawInMTKView_ *, struct MTKView *view)
{
    demo_draw(view);
}

#include "ShaderTypes.h"

#include <stdint.h>
#include <string.h>

struct MTLDevice *g_device = NULL;
struct MTKView *g_view = NULL;

static const NSUInteger kMaxBuffersInFlight = 3;
static const size_t kAlignedUniformsSize = (sizeof(Uniforms) & ~0xFF) + 0x100;

static struct MTLCommandQueue *g_commandQueue = NULL;
static matrix_float4x4 g_projectionMatrix;
static uint8_t g_uniformBufferIndex = 0;
static struct MTLBuffer *g_dynamicUniformBuffer = NULL;
static struct MTLRenderPipelineState *g_pipelineState = NULL;
static struct MTLDepthStencilState *g_depthState = NULL;
static struct MTLBuffer *g_meshvertexBuffer = NULL;
static struct MTLBuffer *g_meshvertexBuffer_Addition = NULL;
float g_rotation = 0.0f;

#include "GCEvent.h"
GCEvent g_inFlightSemaphore[kMaxBuffersInFlight];

static inline matrix_float4x4 matrix4x4_translation(float tx, float ty, float tz)
{
    return (matrix_float4x4){{{1, 0, 0, 0},
                              {0, 1, 0, 0},
                              {0, 0, 1, 0},
                              {tx, ty, tz, 1}}};
}

static inline matrix_float4x4 matrix4x4_rotation(float radians, vector_float3 axis)
{
    axis = vector_normalize(axis);
    float ct = cosf(radians);
    float st = sinf(radians);
    float ci = 1 - ct;
    float x = axis.x, y = axis.y, z = axis.z;

    return (matrix_float4x4){{{ct + x * x * ci, y * x * ci + z * st, z * x * ci - y * st, 0},
                              {x * y * ci - z * st, ct + y * y * ci, z * y * ci + x * st, 0},
                              {x * z * ci + y * st, y * z * ci - x * st, ct + z * z * ci, 0},
                              {0, 0, 0, 1}}};
}

static inline matrix_float4x4 matrix_perspective_right_hand(float fovyRadians, float aspect, float nearZ, float farZ)
{
    float ys = 1 / tanf(fovyRadians * 0.5);
    float xs = ys / aspect;
    float zs = farZ / (nearZ - farZ);

    return (matrix_float4x4){{{xs, 0, 0, 0},
                              {0, ys, 0, 0},
                              {0, 0, zs, -1},
                              {0, 0, nearZ * zs, 0}}};
}

void demo_init(struct MTKView *view)
{
    for (NSUInteger i = 0; i < kMaxBuffersInFlight; ++i)
    {
        g_inFlightSemaphore[i].CreateAutoEventNoThrow(true);
    }

    MTKView_setColorPixelFormat(view, MTLPixelFormatBGRA8Unorm_sRGB);
    MTKView_setDepthStencilPixelFormat(view, MTLPixelFormatDepth32Float_Stencil8);
    MTKView_setSampleCount(view, 1);

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
    struct MTLFunction *vertexFunction = MTLLibrary_newFunctionWithName(defaultLibrary, "vertexShader");
    struct MTLFunction *fragmentFunction = MTLLibrary_newFunctionWithName(defaultLibrary, "fragmentShader");

    struct MTLRenderPipelineDescriptor *pipelineStateDescriptor = MTLRenderPipelineDescriptor_init(MTLRenderPipelineDescriptor_alloc());
    MTLRenderPipelineDescriptor_setLabel(pipelineStateDescriptor, "MyPipeline");
    MTLRenderPipelineDescriptor_setSampleCount(pipelineStateDescriptor, 1);
    MTLRenderPipelineDescriptor_setVertexFunction(pipelineStateDescriptor, vertexFunction);
    MTLRenderPipelineDescriptor_setFragmentFunction(pipelineStateDescriptor, fragmentFunction);
    MTLRenderPipelineDescriptor_setVertexDescriptor(pipelineStateDescriptor, vertexdescriptor);
    MTLRenderPipelineColorAttachmentDescriptor_setPixelFormat(MTLRenderPipelineDescriptor_colorAttachmentAt(pipelineStateDescriptor, 0), MTLPixelFormatBGRA8Unorm_sRGB);
    MTLRenderPipelineDescriptor_setDepthAttachmentPixelFormat(pipelineStateDescriptor, MTLPixelFormatDepth32Float_Stencil8);
    MTLRenderPipelineDescriptor_setStencilAttachmentPixelFormat(pipelineStateDescriptor, MTLPixelFormatDepth32Float_Stencil8);
    MTLFunction_release(vertexFunction);
    MTLFunction_release(fragmentFunction);
    MTLVertexDescriptor_release(vertexdescriptor);

    struct NSError *error = (struct NSError *)(1);
    g_pipelineState = MTLDevice_newRenderPipelineStateWithDescriptor(g_device, pipelineStateDescriptor, &error);
    MTLRenderPipelineDescriptor_release(pipelineStateDescriptor);

    struct MTLDepthStencilDescriptor *depthStateDesc = MTLDepthStencilDescriptor_init(MTLDepthStencilDescriptor_alloc());
    MTLDepthStencilDescriptor_setDepthCompareFunction(depthStateDesc, MTLCompareFunctionLess);
    MTLDepthStencilDescriptor_setDepthWriteEnabled(depthStateDesc, true);

    g_depthState = MTLDevice_newDepthStencilStateWithDescriptor(g_device, depthStateDesc);
    MTLDepthStencilDescriptor_release(depthStateDesc);

    NSUInteger uniformBufferSize = kAlignedUniformsSize * kMaxBuffersInFlight;
    g_dynamicUniformBuffer = MTLDevice_newBufferWithLength(g_device, uniformBufferSize, MTLResourceStorageModeShared);
    MTLBuffer_setLabel(g_dynamicUniformBuffer, "UniformBuffer");

    g_commandQueue = MTLDevice_newCommandQueue(g_device);

    g_projectionMatrix = matrix_perspective_right_hand(65.0f * (M_PI / 180.0f), 1.0f, 0.1f, 100.0f);

    //sem

    //--------------------------------------------------------------------------------------
    // Mesh and VertexFormat Data
    //--------------------------------------------------------------------------------------
    // clang-format off
    static const float g_vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f,  // -X side
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        
        -1.0f,-1.0f,-1.0f,  // -Z side
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        
        -1.0f,-1.0f,-1.0f,  // -Y side
        1.0f,-1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        
        -1.0f, 1.0f,-1.0f,  // +Y side
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        
        1.0f, 1.0f,-1.0f,  // +X side
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        
        -1.0f, 1.0f, 1.0f,  // +Z side
        -1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
    };
    
    static const float g_uv_buffer_data[] = {
        0.0f, 1.0f,  // -X side
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        
        1.0f, 1.0f,  // -Z side
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        
        1.0f, 0.0f,  // -Y side
        1.0f, 1.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        
        1.0f, 0.0f,  // +Y side
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        
        1.0f, 0.0f,  // +X side
        0.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        
        0.0f, 0.0f,  // +Z side
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
    };
    // clang-format on

    g_meshvertexBuffer = MTLDevice_newBufferWithLength(g_device, sizeof(g_vertex_buffer_data), MTLResourceStorageModeShared);
    memcpy(MTLBuffer_contents(g_meshvertexBuffer), g_vertex_buffer_data, sizeof(g_vertex_buffer_data));

    g_meshvertexBuffer_Addition = MTLDevice_newBufferWithLength(g_device, sizeof(g_uv_buffer_data), MTLResourceStorageModeShared);
    memcpy(MTLBuffer_contents(g_meshvertexBuffer_Addition), g_uv_buffer_data, sizeof(g_uv_buffer_data));
}

static void demo_resize(struct MTKView *view, CGSize size)
{
    float aspect = size.width / (float)size.height;
    g_projectionMatrix = matrix_perspective_right_hand(65.0f * (M_PI / 180.0f), aspect, 0.1f, 100.0f);
}

static void demo_draw(struct MTKView *view)
{
    /// Per frame updates here

    g_uniformBufferIndex = (g_uniformBufferIndex + 1) % kMaxBuffersInFlight;

    g_inFlightSemaphore[g_uniformBufferIndex].Wait(INFINITE, false);

    uint32_t uniformBufferOffset = kAlignedUniformsSize * g_uniformBufferIndex;
    void *uniformBufferAddress = reinterpret_cast<void *>(reinterpret_cast<uintptr_t>(MTLBuffer_contents(g_dynamicUniformBuffer)) + uniformBufferOffset);

    Uniforms *uniforms = static_cast<Uniforms *>(uniformBufferAddress);
    uniforms->projectionMatrix = g_projectionMatrix;
    vector_float3 rotationAxis = {1, 1, 0};
    matrix_float4x4 modelMatrix = matrix4x4_rotation(g_rotation, rotationAxis);
    matrix_float4x4 viewMatrix = matrix4x4_translation(0.0, 0.0, -8.0);
    uniforms->modelViewMatrix = matrix_multiply(viewMatrix, modelMatrix);
    g_rotation += .01;

    struct MTLCommandBuffer *commandBuffer = MTLCommandQueue_commandBuffer(g_commandQueue);
    MTLCommandBuffer_setLabel(commandBuffer, "MyCommand");

    MTLCommandBuffer_addCompletedHandler(commandBuffer, reinterpret_cast<void *>(g_uniformBufferIndex), [](void *pUserData, struct MTLCommandBuffer *buffer) -> void {
        g_inFlightSemaphore[reinterpret_cast<uintptr_t>(pUserData)].Set();
    });

    /// Delay getting the currentRenderPassDescriptor until we absolutely need it to avoid
    ///   holding onto the drawable and blocking the display pipeline any longer than necessary
    struct MTLRenderPassDescriptor *renderPassDescriptor = MTKView_currentRenderPassDescriptor(view);
    if (NULL != renderPassDescriptor)
    {
        /// Final pass rendering code here

        struct MTLRenderCommandEncoder *renderEncoder = MTLCommandBuffer_renderCommandEncoderWithDescriptor(commandBuffer, renderPassDescriptor);
        MTLRenderCommandEncoder_setLabel(renderEncoder, "MyRenderEncoder");

        MTLRenderCommandEncoder_pushDebugGroup(renderEncoder, "DrawBox");

        MTLRenderCommandEncoder_setFrontFacingWinding(renderEncoder, MTLWindingCounterClockwise);
        MTLRenderCommandEncoder_setCullMode(renderEncoder, MTLCullModeBack);
        MTLRenderCommandEncoder_setRenderPipelineState(renderEncoder, g_pipelineState);
        MTLRenderCommandEncoder_setDepthStencilState(renderEncoder, g_depthState);

        MTLRenderCommandEncoder_setVertexBuffer(renderEncoder, g_dynamicUniformBuffer, uniformBufferOffset, BufferIndexUniforms);
        MTLRenderCommandEncoder_setFragmentBuffer(renderEncoder, g_dynamicUniformBuffer, uniformBufferOffset, BufferIndexUniforms);

        MTLRenderCommandEncoder_setVertexBuffer(renderEncoder, g_meshvertexBuffer, 0, BufferIndexMeshPositions);
        MTLRenderCommandEncoder_setVertexBuffer(renderEncoder, g_meshvertexBuffer_Addition, 0, BufferIndexMeshGenerics);

        MTLRenderCommandEncoder_drawPrimitives(renderEncoder, MTLPrimitiveTypeTriangle, 0, 12 * 3, 1, 0);

        MTLRenderCommandEncoder_popDebugGroup(renderEncoder);
        MTLRenderCommandEncoder_endEncoding(renderEncoder);

        MTLCommandBuffer_presentDrawable(commandBuffer, MTKView_currentDrawable(view));
    }

    MTLCommandBuffer_commit(commandBuffer);
}

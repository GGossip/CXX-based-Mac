#include "Headers_CXX/Foundation_CXX.h"
#include "Headers_CXX/Dispatch_CXX.h"

#include "Renderer.h"
#include "ShaderTypes.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

static const size_t kAlignedUniformsSize = (sizeof(Uniforms) & ~0xFF) + 0x100;

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

void demo::_init()
{
    _device = MTLCreateSystemDefaultDevice();

    _width = 800;
    _height = 600;
    _view = MTKView_initWithFrame(MTKView_alloc(), NSMakeRect(0, 0, _width, _height), _device);

    MTKView_setColorPixelFormat(_view, MTLPixelFormatBGRA8Unorm_sRGB);
    MTKView_setDepthStencilPixelFormat(_view, MTLPixelFormatDepth32Float_Stencil8);
    MTKView_setSampleCount(_view, 1);
}

void demo::_init2()
{
    _commandQueue = MTLDevice_newCommandQueue(_device);

    //pipelineState
    struct MTLVertexDescriptor *vertexdescriptor = MTLVertexDescriptor_init(MTLVertexDescriptor_alloc());
    MTLVertexBufferLayoutDescriptor_setStride(MTLVertexBufferLayoutDescriptorArray_objectAtIndexedSubscript(MTLVertexDescriptor_layouts(vertexdescriptor), BufferIndexMeshPositions), 12);
    MTLVertexBufferLayoutDescriptor_setStepFunction(MTLVertexBufferLayoutDescriptorArray_objectAtIndexedSubscript(MTLVertexDescriptor_layouts(vertexdescriptor), BufferIndexMeshPositions), MTLVertexStepFunctionPerVertex);
    MTLVertexBufferLayoutDescriptor_setStepRate(MTLVertexBufferLayoutDescriptorArray_objectAtIndexedSubscript(MTLVertexDescriptor_layouts(vertexdescriptor), BufferIndexMeshPositions), 1);

    MTLVertexBufferLayoutDescriptor_setStride(MTLVertexBufferLayoutDescriptorArray_objectAtIndexedSubscript(MTLVertexDescriptor_layouts(vertexdescriptor), BufferIndexMeshPositions), 12);
    MTLVertexBufferLayoutDescriptor_setStepFunction(MTLVertexBufferLayoutDescriptorArray_objectAtIndexedSubscript(MTLVertexDescriptor_layouts(vertexdescriptor), BufferIndexMeshPositions), MTLVertexStepFunctionPerVertex);
    MTLVertexBufferLayoutDescriptor_setStepRate(MTLVertexBufferLayoutDescriptorArray_objectAtIndexedSubscript(MTLVertexDescriptor_layouts(vertexdescriptor), BufferIndexMeshPositions), 1);

    MTLVertexBufferLayoutDescriptor_setStride(MTLVertexBufferLayoutDescriptorArray_objectAtIndexedSubscript(MTLVertexDescriptor_layouts(vertexdescriptor), BufferIndexMeshGenerics), 8);
    MTLVertexBufferLayoutDescriptor_setStepFunction(MTLVertexBufferLayoutDescriptorArray_objectAtIndexedSubscript(MTLVertexDescriptor_layouts(vertexdescriptor), BufferIndexMeshGenerics), MTLVertexStepFunctionPerVertex);
    MTLVertexBufferLayoutDescriptor_setStepRate(MTLVertexBufferLayoutDescriptorArray_objectAtIndexedSubscript(MTLVertexDescriptor_layouts(vertexdescriptor), BufferIndexMeshGenerics), 1);

    MTLVertexAttributeDescriptor_setFormat(MTLVertexAttributeDescriptorArray_objectAtIndexedSubscript(MTLVertexDescriptor_attributes(vertexdescriptor), VertexAttributePosition), MTLVertexFormatFloat3);
    MTLVertexAttributeDescriptor_setOffset(MTLVertexAttributeDescriptorArray_objectAtIndexedSubscript(MTLVertexDescriptor_attributes(vertexdescriptor), VertexAttributePosition), 0);
    MTLVertexAttributeDescriptor_setBufferIndex(MTLVertexAttributeDescriptorArray_objectAtIndexedSubscript(MTLVertexDescriptor_attributes(vertexdescriptor), VertexAttributePosition), BufferIndexMeshPositions);

    MTLVertexAttributeDescriptor_setFormat(MTLVertexAttributeDescriptorArray_objectAtIndexedSubscript(MTLVertexDescriptor_attributes(vertexdescriptor), VertexAttributeTexcoord), MTLVertexFormatFloat2);
    MTLVertexAttributeDescriptor_setOffset(MTLVertexAttributeDescriptorArray_objectAtIndexedSubscript(MTLVertexDescriptor_attributes(vertexdescriptor), VertexAttributeTexcoord), 0);
    MTLVertexAttributeDescriptor_setBufferIndex(MTLVertexAttributeDescriptorArray_objectAtIndexedSubscript(MTLVertexDescriptor_attributes(vertexdescriptor), VertexAttributeTexcoord), BufferIndexMeshGenerics);

    int fd_LibraryCaches;
    {
        char const *filenameautorelease = NSURL_fileSystemRepresentation(NSArrayNSURL_objectAtIndexedSubscript(NSFileManager_URLsForDirectory(NSFileManager_defaultManager(), NSCachesDirectory, NSUserDomainMask), 0));
        //struct stat stbuf;
        //assert(stat(filenameautorelease, &stbuf) == 0 && S_ISDIR(stbuf.st_mode));

        fd_LibraryCaches = open(filenameautorelease, O_RDONLY, O_DIRECTORY);
        assert(fd_LibraryCaches != -1);
    }

    size_t buffersize;
    void *buffer;
    {
        int fd_metallib = openat(fd_LibraryCaches, "Shaders_MacOS.metallib", O_RDONLY);

        struct stat stbuf;
        int res = fstat(fd_metallib, &stbuf);
        assert(res == 0 && S_ISREG(stbuf.st_mode));

        buffersize = stbuf.st_size;
        buffer = malloc(buffersize);
        ssize_t res2 = read(fd_metallib, buffer, buffersize);
        assert(res2 != -1 && res2 == buffersize);

        uint8_t buf_u_assert_only[1];
        ssize_t res3 = read(fd_metallib, buf_u_assert_only, 1);
        assert(res3 != -1 && res3 == 0);

        int res4 = close(fd_metallib);
        assert(res4 == 0);
    }

    dispatch_queue_main_t mainqueue = dispatch_get_main_queue();
    dispatch_data_t dispathdata = dispatch_data_create(buffer, buffersize, mainqueue, [](void *buffer) -> void {
        free(buffer);
    });

    struct NSError *error1 = NULL;
    struct MTLLibrary *myLibrary = MTLDevice_newLibraryWithData(_device, dispathdata, &error1);
    dispatch_release(dispathdata);

    struct MTLFunction *vertexFunction = MTLLibrary_newFunctionWithName(myLibrary, "vertexShader");
    struct MTLFunction *fragmentFunction = MTLLibrary_newFunctionWithName(myLibrary, "fragmentShader");

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
    MTLLibrary_release(myLibrary);
    MTLVertexDescriptor_release(vertexdescriptor);

    struct NSError *error = NULL;
    _pipelineState = MTLDevice_newRenderPipelineStateWithDescriptor(_device, pipelineStateDescriptor, &error);
    MTLRenderPipelineDescriptor_release(pipelineStateDescriptor);

    //depthState
    struct MTLDepthStencilDescriptor *depthStateDesc = MTLDepthStencilDescriptor_init(MTLDepthStencilDescriptor_alloc());
    MTLDepthStencilDescriptor_setDepthCompareFunction(depthStateDesc, MTLCompareFunctionLess);
    MTLDepthStencilDescriptor_setDepthWriteEnabled(depthStateDesc, true);

    _depthState = MTLDevice_newDepthStencilStateWithDescriptor(_device, depthStateDesc);
    MTLDepthStencilDescriptor_release(depthStateDesc);

    _uniformBufferIndex = 0;
    for (NSUInteger i = 0; i < kMaxBuffersInFlight; ++i)
    {
        _inFlightSemaphore[i].CreateManualEventNoThrow(true);
    }

    NSUInteger uniformBufferSize = kAlignedUniformsSize * kMaxBuffersInFlight;
    _dynamicUniformBuffer = MTLDevice_newBufferWithLength(_device, uniformBufferSize, MTLResourceStorageModeShared);
    MTLBuffer_setLabel(_dynamicUniformBuffer, "UniformBuffer");

    float aspect = _width / _height;
    _projectionMatrix = matrix_perspective_right_hand(65.0f * (M_PI / 180.0f), aspect, 0.1f, 100.0f);

    _rotation = 0.0f;

    //--------------------------------------------------------------------------------------
    // Mesh and VertexFormat Data
    //--------------------------------------------------------------------------------------
    // clang-format off
      float const g_vertex_buffer_data[] = {
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
      
      float const g_uv_buffer_data[] = {
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

    _meshvertexBuffer = MTLDevice_newBufferWithLength(_device, sizeof(g_vertex_buffer_data), MTLResourceStorageModeShared);
    memcpy(MTLBuffer_contents(_meshvertexBuffer), g_vertex_buffer_data, sizeof(g_vertex_buffer_data));

    _meshvertexBuffer_Addition = MTLDevice_newBufferWithLength(_device, sizeof(g_uv_buffer_data), MTLResourceStorageModeShared);
    memcpy(MTLBuffer_contents(_meshvertexBuffer_Addition), g_uv_buffer_data, sizeof(g_uv_buffer_data));

    //Load Texture
}

void demo::_resize(float width, float height)
{
    float aspect = _width / _height;
    _projectionMatrix = matrix_perspective_right_hand(65.0f * (M_PI / 180.0f), aspect, 0.1f, 100.0f);
}

void demo::_draw(struct MTKView *view)
{
    /// Per frame updates here
    _uniformBufferIndex = (_uniformBufferIndex + 1) % kMaxBuffersInFlight;

    _inFlightSemaphore[_uniformBufferIndex].Wait(INFINITE, false);

    vector_float3 rotationAxis = {1, 1, 0};
    matrix_float4x4 modelMatrix = matrix4x4_rotation(_rotation, rotationAxis);
    matrix_float4x4 viewMatrix = matrix4x4_translation(0.0, 0.0, -8.0);
    _rotation += 0.01f;

    uint32_t uniformBufferOffset = kAlignedUniformsSize * _uniformBufferIndex;
    void *uniformBufferAddress = reinterpret_cast<void *>(reinterpret_cast<uintptr_t>(MTLBuffer_contents(_dynamicUniformBuffer)) + uniformBufferOffset);
    Uniforms *uniforms = static_cast<Uniforms *>(uniformBufferAddress);
    uniforms->projectionMatrix = _projectionMatrix;
    uniforms->modelViewMatrix = matrix_multiply(viewMatrix, modelMatrix);

    struct MTLCommandBuffer *commandBuffer = MTLCommandQueue_commandBuffer(_commandQueue);
    MTLCommandBuffer_setLabel(commandBuffer, "MyCommand");

    MTLCommandBuffer_addCompletedHandler(commandBuffer, this, _uniformBufferIndex, [](void *pUserData, NSUInteger throttlingIndex, struct MTLCommandBuffer *buffer) -> void {
        static_cast<struct demo *>(pUserData)->_inFlightSemaphore[throttlingIndex].Set();
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
        MTLRenderCommandEncoder_setRenderPipelineState(renderEncoder, _pipelineState);
        MTLRenderCommandEncoder_setDepthStencilState(renderEncoder, _depthState);

        MTLRenderCommandEncoder_setVertexBuffer(renderEncoder, _dynamicUniformBuffer, uniformBufferOffset, BufferIndexUniforms);
        MTLRenderCommandEncoder_setFragmentBuffer(renderEncoder, _dynamicUniformBuffer, uniformBufferOffset, BufferIndexUniforms);

        MTLRenderCommandEncoder_setVertexBuffer(renderEncoder, _meshvertexBuffer, 0, BufferIndexMeshPositions);
        MTLRenderCommandEncoder_setVertexBuffer(renderEncoder, _meshvertexBuffer_Addition, 0, BufferIndexMeshGenerics);

        MTLRenderCommandEncoder_drawPrimitives(renderEncoder, MTLPrimitiveTypeTriangle, 0, 12 * 3, 1, 0);

        MTLRenderCommandEncoder_popDebugGroup(renderEncoder);
        MTLRenderCommandEncoder_endEncoding(renderEncoder);

        MTLCommandBuffer_presentDrawable(commandBuffer, MTKView_currentDrawable(view));
    }

    _inFlightSemaphore[_uniformBufferIndex].Reset();
    MTLCommandBuffer_commit(commandBuffer);
}

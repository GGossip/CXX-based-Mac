#ifndef _RENDERER_H_
#define _RENDERER_H_ 1

#include "Headers_CXX/Metal_CXX.h"
#include "Headers_CXX/MetalKit_CXX.h"
#include "GCEvent.h"

#include <simd/simd.h>

static const NSUInteger kMaxBuffersInFlight = 3;

struct demo
{
    struct MTLDevice *_device;
    
    struct MTKView *_view;
    float _width;
    float _height;
    
    struct MTLCommandQueue *_commandQueue;
    
    struct MTLRenderPipelineState *_pipelineState;
    struct MTLDepthStencilState *_depthState;
    
    uint8_t _uniformBufferIndex;
    GCEvent _inFlightSemaphore[kMaxBuffersInFlight];
    struct MTLBuffer *_dynamicUniformBuffer;
    
    matrix_float4x4 _projectionMatrix;
    
    float _rotation;
    struct MTLBuffer *_meshvertexBuffer;
    struct MTLBuffer *_meshvertexBuffer_Addition;
    
    void _init();
    
    void _init2();
    
    void _resize(float width, float height);
    
    void _draw(struct MTKView *view);
};

#endif
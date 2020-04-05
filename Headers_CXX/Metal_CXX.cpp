#include "Metal_CXX.h"

#include <objc/objc.h>
#include <objc/objc-runtime.h>

struct MTLDevice : public objc_object
{
    MTLDevice() = delete;
};

struct MTLRenderPipelineDescriptor : public objc_object
{
    MTLRenderPipelineDescriptor() = delete;
};

struct MTLRenderPipelineState : public objc_object
{
    MTLRenderPipelineState() = delete;
};

struct MTLVertexDescriptor *
MTLVertexDescriptor_alloc()
{
    struct objc_object *vertexdescriptor = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        objc_getClass("MTLVertexDescriptor"),
        sel_registerName("alloc"));
    return reinterpret_cast<struct MTLVertexDescriptor *>(vertexdescriptor);
}

struct MTLVertexDescriptor *MTLVertexDescriptor_init(struct MTLVertexDescriptor *self)
{
    struct objc_object *vertexdescriptor = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("init"));
    return reinterpret_cast<struct MTLVertexDescriptor *>(vertexdescriptor);
}

struct MTLVertexBufferLayoutDescriptorArray *MTLVertexDescriptor_layouts(struct MTLVertexDescriptor *self)
{
    struct objc_object *vertexdescriptor_layouts = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("layouts"));
    return reinterpret_cast<struct MTLVertexBufferLayoutDescriptorArray *>(vertexdescriptor_layouts);
}

struct MTLVertexBufferLayoutDescriptor *MTLVertexBufferLayoutDescriptorArray_objectAtIndexedSubscript(struct MTLVertexBufferLayoutDescriptorArray *self, NSUInteger index)
{
    struct objc_object *vertexdescriptor_layout = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *, NSUInteger)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("objectAtIndexedSubscript:"),
        index);
    return reinterpret_cast<struct MTLVertexBufferLayoutDescriptor *>(vertexdescriptor_layout);
}

void MTLVertexBufferLayoutDescriptor_setStride(struct MTLVertexBufferLayoutDescriptor *self, NSUInteger stride)
{
    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, NSUInteger)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("setStride:"),
        stride);
}

void MTLVertexBufferLayoutDescriptor_setStepFunction(struct MTLVertexBufferLayoutDescriptor *self, MTLVertexStepFunction stepFunction)
{
    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, NSUInteger)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("setStepFunction:"),
        stepFunction);
}

void MTLVertexBufferLayoutDescriptor_setStepRate(struct MTLVertexBufferLayoutDescriptor *self, NSUInteger stepRate)
{
    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, NSUInteger)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("setStepRate:"),
        stepRate);
}

struct MTLVertexAttributeDescriptorArray *MTLVertexDescriptor_attributes(struct MTLVertexDescriptor *self)
{
    struct objc_object *vertexdescriptor_attributes = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("attributes"));
    return reinterpret_cast<struct MTLVertexAttributeDescriptorArray *>(vertexdescriptor_attributes);
}

struct MTLVertexAttributeDescriptor *MTLVertexAttributeDescriptorArray_objectAtIndexedSubscript(struct MTLVertexAttributeDescriptorArray *self, NSUInteger index)
{
    struct objc_object *vertexdescriptor_attribute = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *, NSUInteger)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("objectAtIndexedSubscript:"),
        index);
    return reinterpret_cast<struct MTLVertexAttributeDescriptor *>(vertexdescriptor_attribute);
}

void MTLVertexAttributeDescriptor_setFormat(struct MTLVertexAttributeDescriptor *self, MTLVertexFormat format)
{
    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, NSUInteger)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("setFormat:"),
        format);
}

void MTLVertexAttributeDescriptor_setOffset(struct MTLVertexAttributeDescriptor *self, NSUInteger offset)
{
    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, NSUInteger)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("setOffset:"),
        offset);
}

void MTLVertexAttributeDescriptor_setBufferIndex(struct MTLVertexAttributeDescriptor *self, NSUInteger bufferIndex)
{
    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, NSUInteger)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("setBufferIndex:"),
        bufferIndex);
}

struct MTLRenderPipelineDescriptor *MTLRenderPipelineDescriptor_alloc()
{
    struct objc_object *pipelinedescriptor = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        objc_getClass("MTLRenderPipelineDescriptor"),
        sel_registerName("alloc"));
    return reinterpret_cast<struct MTLRenderPipelineDescriptor *>(pipelinedescriptor);
}

struct MTLRenderPipelineDescriptor *MTLRenderPipelineDescriptor_init(struct MTLRenderPipelineDescriptor *self)
{
    struct objc_object *pipelinedescriptor = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("init"));
    return reinterpret_cast<struct MTLRenderPipelineDescriptor *>(pipelinedescriptor);
}

void MTLRenderPipelineDescriptor_setLabel(struct MTLRenderPipelineDescriptor *self, struct NSString *label)
{
    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, struct objc_object *)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("setLabel:"),
        reinterpret_cast<struct objc_object *>(label));
}

void MTLRenderPipelineDescriptor_setVertexFunction(struct MTLRenderPipelineDescriptor *self, struct MTLFunction *vertexFunction)
{
    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, struct objc_object *)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("setVertexFunction:"),
        reinterpret_cast<struct objc_object *>(vertexFunction));
}

void MTLRenderPipelineDescriptor_setFragmentFunction(struct MTLRenderPipelineDescriptor *self, struct MTLFunction *fragmentFunction)
{
    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, struct objc_object *)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("setFragmentFunction:"),
        reinterpret_cast<struct objc_object *>(fragmentFunction));
}

void MTLRenderPipelineDescriptor_setVertexDescriptor(struct MTLRenderPipelineDescriptor *self, struct MTLVertexDescriptor *vertexDescriptor)
{
    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, struct objc_object *)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("setVertexDescriptor:"),
        reinterpret_cast<struct objc_object *>(vertexDescriptor));
}

void MTLRenderPipelineDescriptor_setSampleCount(struct MTLRenderPipelineDescriptor *self, NSUInteger sampleCount)
{
    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, NSUInteger)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("setSampleCount:"),
        sampleCount);
}

struct MTLRenderPipelineColorAttachmentDescriptorArray *MTLRenderPipelineDescriptor_colorAttachments(struct MTLRenderPipelineDescriptor *self)
{
    struct objc_object *renderpipelinedescriptor_colorattachments = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("colorAttachments"));
    return reinterpret_cast<struct MTLRenderPipelineColorAttachmentDescriptorArray *>(renderpipelinedescriptor_colorattachments);
}

struct MTLRenderPipelineColorAttachmentDescriptor *MTLRenderPipelineColorAttachmentDescriptorArray_objectAtIndexedSubscript(struct MTLRenderPipelineColorAttachmentDescriptorArray *self, NSUInteger attachmentIndex)
{
    struct objc_object *renderpipelinedescriptor_colorattachment = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *, NSUInteger)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("objectAtIndexedSubscript:"),
        attachmentIndex);
    return reinterpret_cast<struct MTLRenderPipelineColorAttachmentDescriptor *>(renderpipelinedescriptor_colorattachment);
}

void MTLRenderPipelineColorAttachmentDescriptor_setPixelFormat(struct MTLRenderPipelineColorAttachmentDescriptor *self, MTLPixelFormat pixelFormat)
{
    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, MTLPixelFormat)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("setPixelFormat:"),
        pixelFormat);
}

void MTLRenderPipelineDescriptor_setDepthAttachmentPixelFormat(struct MTLRenderPipelineDescriptor *self, MTLPixelFormat pixelFormat)
{
    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, MTLPixelFormat)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("setDepthAttachmentPixelFormat:"),
        pixelFormat);
}

void MTLRenderPipelineDescriptor_setStencilAttachmentPixelFormat(struct MTLRenderPipelineDescriptor *self, MTLPixelFormat pixelFormat)
{
    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, MTLPixelFormat)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("setStencilAttachmentPixelFormat:"),
        pixelFormat);
}

void MTLRenderPipelineDescriptor_release(struct MTLRenderPipelineDescriptor *self)
{
    return NSObject_release(reinterpret_cast<struct NSObject *>(self));
}

NSUInteger MTLRenderPipelineDescriptor_retainCount(struct MTLRenderPipelineDescriptor *self)
{
    return NSObject_retainCount(reinterpret_cast<struct NSObject *>(self));
}

struct MTLRenderPipelineState *MTLDevice_newRenderPipelineStateWithDescriptor(struct MTLDevice *self, struct MTLRenderPipelineDescriptor *descriptor, struct NSError **error)
{
    struct objc_object *pipelinestate = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *, struct objc_object *, struct objc_object **)>(objc_msgSend)(
        self,
        sel_registerName("newRenderPipelineStateWithDescriptor:error:"),
        descriptor,
        reinterpret_cast<struct objc_object **>(error));
    return static_cast<MTLRenderPipelineState *>(pipelinestate);
}

struct MTLLibrary *MTLDevice_newDefaultLibrary(struct MTLDevice *self)
{
    struct objc_object *library = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("newDefaultLibrary"));
    return reinterpret_cast<struct MTLLibrary *>(library);
}

struct MTLFunction *MTLLibrary_newFunctionWithName(struct MTLLibrary *self, struct NSString *functionName)
{
    struct objc_object *function = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *, struct objc_object *)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("newFunctionWithName:"),
        reinterpret_cast<struct objc_object *>(functionName));
    return reinterpret_cast<struct MTLFunction *>(function);
}

void MTLFunction_release(struct MTLFunction *self)
{
    return NSObject_release(reinterpret_cast<struct NSObject *>(self));
}

NSUInteger MTLFunction_retainCount(struct MTLFunction *self)
{
    return NSObject_retainCount(reinterpret_cast<struct NSObject *>(self));
}

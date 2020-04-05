#include "Metal_CXX.h"

#include <objc/objc.h>
#include <objc/objc-runtime.h>

struct MTLVertexDescriptor *MTLVertexDescriptor_alloc()
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
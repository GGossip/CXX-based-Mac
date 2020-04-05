#include "Metal_CXX.h"

#include <objc/objc.h>
#include <objc/objc-runtime.h>

struct MTLVertexDescriptor *MTLVertexDescriptor_alloc()
{
    struct objc_object *mtlVertexDescriptor = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        objc_getClass("MTLVertexDescriptor"),
        sel_registerName("alloc"));
    return reinterpret_cast<struct MTLVertexDescriptor *>(mtlVertexDescriptor);
}

struct MTLVertexDescriptor *MTLVertexDescriptor_init(struct MTLVertexDescriptor *self)
{
    struct objc_object *mtlVertexDescriptor = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("init"));
    return reinterpret_cast<struct MTLVertexDescriptor *>(mtlVertexDescriptor);
}

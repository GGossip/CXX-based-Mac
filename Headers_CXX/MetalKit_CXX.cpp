#include "MetalKit_CXX.h"

#include <objc/objc.h>
#include <objc/objc-runtime.h>

#include <assert.h>

struct MTKView *MTKView_alloc()
{
    struct objc_object *view = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        objc_getClass("MTKView"),
        sel_registerName("alloc"));
    return reinterpret_cast<struct MTKView *>(view);
}

struct MTKView *MTKView_initWithFrame(MTKView *self, CGRect frameRect, struct MTLDevice *device)
{
    struct objc_object *view = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *, CGRect, struct objc_object *)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("initWithFrame:device:"),
        frameRect,
        reinterpret_cast<struct objc_object *>(device));
    return reinterpret_cast<struct MTKView *>(view);
}

void NSViewController_setView(struct NSViewController *self, struct MTKView *view)
{
    NSViewController_setView(self, reinterpret_cast<struct NSView *>(view));
}

struct MTKViewDelegate_Class *MTKViewDelegate_allocClass(
    char const *classname,
    void (*_I_MTKViewDelegate_drawableSizeWillChange_)(struct NSApplicationDelegate *, struct MTKViewDelegate_drawableSizeWillChange_ *, struct MTKView *view, CGSize size),
    void (*_I_MTKViewDelegate_drawInMTKView_)(struct NSApplicationDelegate *, struct MTKViewDelegate_drawInMTKView_ *, struct MTKView *view))
{
    Class class_MTKViewDelegate_CXX;
    {
        class_MTKViewDelegate_CXX = objc_allocateClassPair(
            objc_getClass("NSObject"),
            classname,
            0);
        assert(class_MTKViewDelegate_CXX != NULL);

        BOOL result_1 = class_addMethod(
            class_MTKViewDelegate_CXX,
            sel_registerName("mtkView:drawableSizeWillChange:"),
            reinterpret_cast<IMP>(_I_MTKViewDelegate_drawableSizeWillChange_),
            "v@:@{CGSize=dd}");
        assert(result_1 != NO);

        BOOL result_2 = class_addMethod(
            class_MTKViewDelegate_CXX,
            sel_registerName("drawInMTKView:"),
            reinterpret_cast<IMP>(_I_MTKViewDelegate_drawInMTKView_),
            "v@:@");
        assert(result_2 != NO);
    }

    return reinterpret_cast<struct MTKViewDelegate_Class *>(class_MTKViewDelegate_CXX);
}

struct MTKViewDelegate *MTKViewDelegate_alloc(struct MTKViewDelegate_Class *class_MTKViewDelegate_CXX)
{
    struct objc_object *delegate = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        reinterpret_cast<Class>(class_MTKViewDelegate_CXX),
        sel_registerName("alloc"));

    return reinterpret_cast<struct MTKViewDelegate *>(delegate);
}

void MTKView_setDelegate(struct MTKView *self, struct MTKViewDelegate *delegate)
{
    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, struct objc_object *)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("setDelegate:"),
        reinterpret_cast<struct objc_object *>(delegate));
}

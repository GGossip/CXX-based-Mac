#include "../AppKit/NSView.h
#include "../AppKit/NSView_Impl.h"

#include <TargetConditionals.h>
#if TARGET_OS_IOS
#include <objc/message.h>
#include <objc/runtime.h>
#elif TARGET_OS_OSX
#include <objc/objc-runtime.h>
#else
#error Unknown Target
#endif

struct NSView *NSView_alloc()
{
    struct objc_object *view = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        objc_getClass("NSView"),
        sel_registerName("alloc"));
    return static_cast<struct NSView *>(view);
}

struct NSView *NSView_initWithFrame(NSView *self, NSRect frameRect)
{
    struct objc_object *view = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *, NSRect)>(objc_msgSend)(
        self,
        sel_registerName("initWithFrame:"),
        frameRect);
    return static_cast<struct NSView *>(view);
}


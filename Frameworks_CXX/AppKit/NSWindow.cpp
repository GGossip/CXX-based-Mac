#include "../AppKit/NSWindow.h
#include "../AppKit/NSWindow_Impl.h"

#include <TargetConditionals.h>
#if TARGET_OS_IOS
#include <objc/message.h>
#include <objc/runtime.h>
#elif TARGET_OS_OSX
#include <objc/objc-runtime.h>
#else
#error Unknown Target
#endif

struct NSWindow *NSWindow_alloc()
{
    struct objc_object *window = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        objc_getClass("NSWindow"),
        sel_registerName("alloc"));

    return static_cast<struct NSWindow *>(window);
}

struct NSWindow *NSWindow_initWithContentRect(struct NSWindow *self, NSRect rect, NSWindowStyleMask styleMask, NSBackingStoreType backing, bool defer)
{
    struct objc_object *window = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *, NSRect, NSWindowStyleMask, NSBackingStoreType, BOOL)>(objc_msgSend)(
        self,
        sel_registerName("initWithContentRect:styleMask:backing:defer:"),
        rect,
        styleMask,
        backing,
        (defer != false) ? YES : NO);
    return static_cast<struct NSWindow *>(window);
}

void NSWindow_setContentViewController(struct NSWindow *self, struct NSViewController *contentViewController)
{
    return reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, struct objc_object *)>(objc_msgSend)(
        self,
        sel_registerName("setContentViewController:"),
        contentViewController);
}

void NSWindow_makeKeyAndOrderFront(struct NSWindow *self, void *sender)
{
    return reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, struct objc_object *)>(objc_msgSend)(
        self,
        sel_registerName("makeKeyAndOrderFront:"),
        reinterpret_cast<struct objc_object *>(sender));
}
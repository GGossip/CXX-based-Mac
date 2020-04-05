#include "CXX_AppKit.h"

#include <objc/objc.h>
#include <objc/objc-runtime.h>

struct NSWindow *NSWindow_alloc()
{
    struct objc_object *window = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        objc_getClass("NSWindow"),
        sel_registerName("alloc"));

    return reinterpret_cast<struct NSWindow *>(window);
}

struct NSWindow *NSWindow_initWithContentRect(struct NSWindow *self, NSRect rect, NSWindowStyleMask styleMask, NSBackingStoreType backing, bool defer)
{
    struct objc_object *window = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *, NSRect, NSWindowStyleMask, NSBackingStoreType, BOOL)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("initWithContentRect:styleMask:backing:defer:"),
        rect,
        styleMask,
        backing,
        defer);
    return reinterpret_cast<struct NSWindow *>(window);
}

void NSWindow_setContentViewController(struct NSWindow *self, void *contentViewController)
{
    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, struct objc_object *)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("setContentViewController:"),
        reinterpret_cast<struct objc_object *>(contentViewController));
}

void NSWindow_makeKeyAndOrderFront(struct NSWindow *self, void *sender)
{
    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, struct objc_object *)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("makeKeyAndOrderFront:"),
        reinterpret_cast<struct objc_object *>(sender));
}
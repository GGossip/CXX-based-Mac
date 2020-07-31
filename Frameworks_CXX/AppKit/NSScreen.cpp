#include "../AppKit/NSScreen.h
#include "../AppKit/NSScreen_Impl.h"

#include <TargetConditionals.h>
#if TARGET_OS_IOS
#include <objc/message.h>
#include <objc/runtime.h>
#elif TARGET_OS_OSX
#include <objc/objc-runtime.h>
#else
#error Unknown Target
#endif

struct NSScreen *NSScreen_mainScreen()
{
    struct objc_object *screen = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        objc_getClass("NSScreen"),
        sel_registerName("mainScreen"));

    return static_cast<struct NSScreen *>(screen);
}

NSRect NSScreen_frame(struct NSScreen *self)
{
    assert(sizeof(NSRect) != 1 && sizeof(NSRect) != 2 && sizeof(NSRect) != 4 && sizeof(NSRect) != 8);
    NSRect _frame = reinterpret_cast<NSRect (*)(struct objc_object *, struct objc_selector *)>(objc_msgSend_stret)(
        self,
        sel_registerName("frame"));
    return _frame;
}


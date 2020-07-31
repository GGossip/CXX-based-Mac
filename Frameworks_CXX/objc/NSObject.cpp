#include "../objc/NSObject.h"
#include "../objc/NSObject_Impl.h"

#include <TargetConditionals.h>
#if TARGET_OS_IOS
#include <objc/message.h>
#include <objc/runtime.h>
#elif TARGET_OS_OSX
#include <objc/objc-runtime.h>
#else
#error Unknown Target
#endif

struct NSObject *NSObject_init(struct NSObject *self)
{
    struct objc_object *object = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *)>(objc_msgSend)(
        self,
        sel_registerName("init"));
    return static_cast<struct NSObject *>(object);
}

void NSObject_release(struct NSObject *self)
{
    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *)>(objc_msgSend)(
        self,
        sel_registerName("release"));
}

NSUInteger NSObject_retainCount(struct NSObject *self)
{
    NSUInteger retaincount = reinterpret_cast<NSUInteger (*)(struct objc_object *, struct objc_selector *)>(objc_msgSend)(
        self,
        sel_registerName("retainCount"));
    return retaincount;
}

#include "NSRuntime_CXX.h"
#include "NSRuntime_CXX_IMPL.h"

#include <objc/objc-runtime.h>

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

struct NSString *NSString_stringWithUTF8String(char const *nullTerminatedCString)
{
    struct objc_object *string = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *, char const *)>(objc_msgSend)(
        objc_getClass("NSString"),
        sel_registerName("stringWithUTF8String:"),
        nullTerminatedCString);
    return static_cast<struct NSString *>(string);
}

void NSString_release(struct NSString *self)
{
    return NSObject_release(self);
}

NSUInteger NSString_retainCount(struct NSString *self)
{
    return NSObject_retainCount(self);
}

#include <objc/objc.h>
#include <objc/runtime.h>
#include <objc/message.h>

#include "CXX_AppKit.h"

void _I_AppViewController_loadView(struct objc_object *self, struct objc_selector *_cmd)
{
    struct objc_object *nsview = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        objc_getClass("NSView"),
        sel_registerName("alloc"));

    NSRect rect = NSMakeRect(0, 0, 800, 600);
    reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *, NSRect)>(objc_msgSend)(
        nsview,
        sel_registerName("initWithFrame:"),
        rect);

    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, struct objc_object *)>(objc_msgSend)(
        self,
        sel_registerName("setView:"),
        nsview);
}

void _I_AppViewController_viewDidLoad(struct objc_object *self, struct objc_selector *_cmd)
{
    struct objc_super super = {self, class_getSuperclass(object_getClass(self))};
    reinterpret_cast<void (*)(struct objc_super *, struct objc_selector *)>(objc_msgSendSuper)(&super, _cmd);
}

void _I_AppViewController_setRepresentedObject_(struct objc_object *self, struct objc_selector *_cmd, struct objc_object *representedObject)
{
    struct objc_super super = {self, class_getSuperclass(object_getClass(self))};
    reinterpret_cast<void (*)(struct objc_super *, struct objc_selector *, struct objc_object *)>(objc_msgSendSuper)(&super, _cmd, representedObject);
}
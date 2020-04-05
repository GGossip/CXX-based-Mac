#include <objc/objc.h>
#include <objc/runtime.h>
#include <objc/message.h>
#include <assert.h>

#include "CXX_AppKit.h"

void _I_AppViewController_loadView(struct objc_object *self, struct objc_selector *_cmd);

void _I_AppViewController_viewDidLoad(struct objc_object *self, struct objc_selector *_cmd);

void _I_AppViewController_setRepresentedObject_(struct objc_object *self, struct objc_selector *_cmd, struct objc_object *representedObject);

void _I_AppDelegate_applicationDidFinishLaunching_(struct objc_object *self, struct objc_selector *_cmd, struct objc_object *aNotification)
{
    NSSize windowSize = NSMakeSize(480, 480);
    struct objc_object *mainScreen = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        objc_getClass("NSScreen"),
        sel_registerName("mainScreen"));

    assert(sizeof(NSRect) != 1 && sizeof(NSRect) != 2 && sizeof(NSRect) != 4 && sizeof(NSRect) != 8);
    NSSize screenSize = reinterpret_cast<NSRect (*)(struct objc_object *, struct objc_selector *)>(objc_msgSend_stret)(mainScreen, sel_registerName("frame")).size;

    NSRect rect = NSMakeRect(screenSize.width / 2 - windowSize.width / 2,
                             screenSize.height / 2 - windowSize.height / 2,
                             windowSize.width,
                             windowSize.height);

    struct NSWindow *window = NSWindow_initWithContentRect(
        NSWindow_alloc(),
        rect,
        NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable,
        NSBackingStoreBuffered,
        NO);

    Class class_ViewController;
    {
        class_ViewController = objc_allocateClassPair(
            objc_getClass("NSViewController"),
            "ViewController",
            0);

        BOOL res;

        res = class_addMethod(
            class_ViewController,
            sel_registerName("loadView"),
            reinterpret_cast<IMP>(_I_AppViewController_loadView),
            "v@:");
        assert(res != NO);

        res = class_addMethod(
            class_ViewController,
            sel_registerName("viewDidLoad"),
            reinterpret_cast<IMP>(_I_AppViewController_viewDidLoad),
            "v@:");
        assert(res != NO);

        res = class_addMethod(
            class_ViewController,
            sel_registerName("setRepresentedObject:"),
            reinterpret_cast<IMP>(_I_AppViewController_setRepresentedObject_),
            "v@:@");
        assert(res != NO);
    }

    struct objc_object *controller = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        class_ViewController,
        sel_registerName("alloc"));

    controller = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *, struct objc_object *, struct objc_object *)>(objc_msgSend)(
        controller,
        sel_registerName("initWithNibName:bundle:"),
        NULL,
        NULL);

#if 0
    struct objc_object *view = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *)>(objc_msgSend)(controller, sel_registerName("view"));

    struct objc_object *contentview = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *)>(objc_msgSend)(window, sel_registerName("contentView"));

    assert(sizeof(NSRect) != 1 && sizeof(NSRect) != 2 && sizeof(NSRect) != 4 && sizeof(NSRect) != 8);
    NSRect bounds = reinterpret_cast<NSRect (*)(struct objc_object *, struct objc_selector *)>(objc_msgSend_stret)(contentview, sel_registerName("bounds"));

    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, NSRect)>(objc_msgSend)(
        view,
        sel_registerName("setFrame:"),
        bounds);
#endif

    NSWindow_setContentViewController(window, controller);

    NSWindow_makeKeyAndOrderFront(window, NULL);
}

void _I_AppDelegate_applicationWillTerminate_(struct objc_object *self, struct objc_selector *_cmd, struct objc_object *aNotification)
{
}

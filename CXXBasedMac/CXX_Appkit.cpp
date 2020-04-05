#include "CXX_AppKit.h"

#include <objc/objc.h>
#include <objc/objc-runtime.h>

#include <assert.h>

struct NSScreen *NSScreen_mainScreen()
{
    struct objc_object *screen = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        objc_getClass("NSScreen"),
        sel_registerName("mainScreen"));

    return reinterpret_cast<struct NSScreen *>(screen);
}

NSRect NSScreen_frame(struct NSScreen *self)
{
    assert(sizeof(NSRect) != 1 && sizeof(NSRect) != 2 && sizeof(NSRect) != 4 && sizeof(NSRect) != 8);
    NSRect _frame = reinterpret_cast<NSRect (*)(struct objc_object *, struct objc_selector *)>(objc_msgSend_stret)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("frame"));
    return _frame;
}

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

void NSWindow_setContentViewController(struct NSWindow *self, struct NSViewController *contentViewController)
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

struct NSView *NSView_alloc()
{
    struct objc_object *view = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        objc_getClass("NSView"),
        sel_registerName("alloc"));
    return reinterpret_cast<struct NSView *>(view);
}

struct NSView *NSView_initWithFrame(NSView *self, NSRect frameRect)
{
    struct objc_object *view = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *, NSRect)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("initWithFrame:"),
        frameRect);
    return reinterpret_cast<struct NSView *>(view);
}

struct NSApplicationDelegate *NSApplicationDelegate_alloc(
    void (*_I_NSApplicationDelegate_applicationDidFinishLaunching_)(struct NSApplicationDelegate *, void *_cmd, void *aNotification),
    void (*_I_NSApplicationDelegate_applicationWillTerminate_)(struct NSApplicationDelegate *, void *_cmd, void *aNotification))
{
    Class class_AppDelegate;
    {
        //objc_object *protocol_NSApplicationDelegate = objc_getProtocol("NSApplicationDelegate");
        //return NULL why???

        class_AppDelegate = objc_allocateClassPair(
            objc_getClass("NSObject"),
            "AppDelegate",
            0);

        BOOL res;

        res = class_addMethod(
            class_AppDelegate,
            sel_registerName("applicationDidFinishLaunching:"),
            reinterpret_cast<IMP>(_I_NSApplicationDelegate_applicationDidFinishLaunching_),
            "v@:@");
        assert(res != NO);

        res = class_addMethod(
            class_AppDelegate,
            sel_registerName("applicationWillTerminate:"),
            reinterpret_cast<IMP>(_I_NSApplicationDelegate_applicationWillTerminate_),
            "v@:@");
        assert(res != NO);

        //res = class_addProtocol(
        //      class_MyDelegate,
        //      protocol_NSApplicationDelegate);

        //assert(res != NO);

        //objc_registerClassPair(class_AppDelegate);

        //res = class_conformsToProtocol(class_MyDelegate,protocol_NSApplicationDelegate);
        //assert(res != NO);
    }

    struct objc_object *delegate = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        class_AppDelegate,
        sel_registerName("alloc"));

    return reinterpret_cast<struct NSApplicationDelegate *>(delegate);
}

struct NSViewController *NSViewController_alloc(
    void (*_I_NSViewController_loadView)(struct NSViewController *, struct NSViewController_loadView *),
    void (*_I_NSViewController_viewDidLoad)(struct NSViewController *, struct NSViewController_viewDidLoad *),
    void (*_I_NSViewController_setRepresentedObject_)(struct NSViewController *, struct NSViewController_setRepresentedObject_ *, void *representedObject))
{
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
            reinterpret_cast<IMP>(_I_NSViewController_loadView),
            "v@:");
        assert(res != NO);

        res = class_addMethod(
            class_ViewController,
            sel_registerName("viewDidLoad"),
            reinterpret_cast<IMP>(_I_NSViewController_viewDidLoad),
            "v@:");
        assert(res != NO);

        res = class_addMethod(
            class_ViewController,
            sel_registerName("setRepresentedObject:"),
            reinterpret_cast<IMP>(_I_NSViewController_setRepresentedObject_),
            "v@:@");
        assert(res != NO);
    }

    struct objc_object *viewcontroller = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        class_ViewController,
        sel_registerName("alloc"));

    return reinterpret_cast<struct NSViewController *>(viewcontroller);
}

struct NSViewController *NSViewController_initWithNibName(struct NSViewController *self, void *nibNameOrNil, void *nibBundleOrNil)
{
    struct objc_object *viewcontroller = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *, struct objc_object *, struct objc_object *)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("initWithNibName:bundle:"),
        reinterpret_cast<struct objc_object *>(nibNameOrNil),
        reinterpret_cast<struct objc_object *>(nibBundleOrNil));

    return reinterpret_cast<struct NSViewController *>(viewcontroller);
}

void NSViewController_setView(struct NSViewController *self, NSView *view)
{
    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, struct objc_object *)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(self),
        sel_registerName("setView:"),
        reinterpret_cast<struct objc_object *>(view));
}

void NSViewController_super_viewDidLoad(struct NSViewController *self, struct NSViewController_viewDidLoad *_cmd)
{
    struct objc_super super = {
        reinterpret_cast<struct objc_object *>(self),
        class_getSuperclass(object_getClass(reinterpret_cast<struct objc_object *>(self)))};

    reinterpret_cast<void (*)(struct objc_super *, struct objc_selector *)>(objc_msgSendSuper)(
        &super,
        reinterpret_cast<struct objc_selector *>(_cmd));
}

void NSViewController_super_setRepresentedObject_(struct NSViewController *self, struct NSViewController_setRepresentedObject_ *_cmd, void *representedObject)
{
    struct objc_super super = {
        reinterpret_cast<struct objc_object *>(self),
        class_getSuperclass(object_getClass(reinterpret_cast<struct objc_object *>(self)))};

    reinterpret_cast<void (*)(struct objc_super *, struct objc_selector *, struct objc_object *)>(objc_msgSendSuper)(
        &super,
        reinterpret_cast<struct objc_selector *>(_cmd),
        reinterpret_cast<struct objc_object *>(representedObject));
}
#include <objc/objc.h>
#include <objc/message.h>
#include <objc/runtime.h>
#include <objc/NSObjCRuntime.h>
#include <assert.h>

extern "C" int NSApplicationMain(int argc, const char *argv[]);

static void _I_AppDelegate_applicationDidFinishLaunching_(struct objc_object *self, struct objc_selector *_cmd, struct objc_object *aNotification);

static void _I_AppDelegate_applicationWillTerminate_(struct objc_object *self, struct objc_selector *_cmd, struct objc_object *aNotification);

int main(int argc, const char *argv[])
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
            reinterpret_cast<IMP>(_I_AppDelegate_applicationDidFinishLaunching_),
            "v@:@");
        assert(res != NO);

        res = class_addMethod(
            class_AppDelegate,
            sel_registerName("applicationWillTerminate:"),
            reinterpret_cast<IMP>(_I_AppDelegate_applicationWillTerminate_),
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

    struct objc_object *sharedApplication = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *)>(objc_msgSend)(
        reinterpret_cast<struct objc_object *>(objc_getClass("NSApplication")),
        sel_registerName("sharedApplication"));

    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, struct objc_object *)>(objc_msgSend)(
        sharedApplication,
        sel_registerName("setDelegate:"),
        delegate);

    int result = NSApplicationMain(argc, argv);
    return result;
}

typedef double CGFloat;

typedef struct __attribute__((objc_boxable))
{
    CGFloat width;
    CGFloat height;
} CGSize;

typedef struct __attribute__((objc_boxable))
{
    CGFloat x;
    CGFloat y;
} CGPoint;

typedef struct __attribute__((objc_boxable))
{
    CGPoint origin;
    CGSize size;
} CGRect;

typedef CGSize NSSize;

typedef CGRect NSRect;

static inline NSSize NSMakeSize(CGFloat w, CGFloat h)
{
    NSSize s;
    s.width = w;
    s.height = h;
    return s;
}

static inline NSRect NSMakeRect(CGFloat x, CGFloat y, CGFloat w, CGFloat h)
{
    NSRect r;
    r.origin.x = x;
    r.origin.y = y;
    r.size.width = w;
    r.size.height = h;
    return r;
}

typedef NSUInteger NSWindowStyleMask;

enum
{
    NSWindowStyleMaskBorderless = 0,
    NSWindowStyleMaskTitled = 1 << 0,
    NSWindowStyleMaskClosable = 1 << 1,
    NSWindowStyleMaskMiniaturizable = 1 << 2,
    NSWindowStyleMaskResizable = 1 << 3
};

typedef NSUInteger NSBackingStoreType;
enum
{

    NSBackingStoreRetained = 0,
    NSBackingStoreNonretained = 1,
    NSBackingStoreBuffered = 2,
};

static void _I_AppViewController_loadView(struct objc_object *self, struct objc_selector *_cmd);

static void _I_AppViewController_viewDidLoad(struct objc_object *self, struct objc_selector *_cmd);

static void _I_AppViewController_setRepresentedObject_(struct objc_object *self, struct objc_selector *_cmd, struct objc_object *representedObject);

static void _I_AppDelegate_applicationDidFinishLaunching_(struct objc_object *self, struct objc_selector *_cmd, struct objc_object *aNotification)
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

    struct objc_object *window = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *)>(objc_msgSend)(
        reinterpret_cast<objc_object *>(objc_getClass("NSWindow")),
        sel_registerName("alloc"));

    window = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *, NSRect, NSWindowStyleMask, NSBackingStoreType, BOOL)>(objc_msgSend)(
        window,
        sel_registerName("initWithContentRect:styleMask:backing:defer:"),
        rect,
        NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable,
        NSBackingStoreBuffered,
        NO);

    Class class_AppViewController;
    {
        class_AppViewController = objc_allocateClassPair(
            objc_getClass("NSViewController"),
            "AppViewController",
            0);

        BOOL res;

        res = class_addMethod(
            class_AppViewController,
            sel_registerName("loadView"),
            reinterpret_cast<IMP>(_I_AppViewController_loadView),
            "v@:");
        assert(res != NO);

        res = class_addMethod(
            class_AppViewController,
            sel_registerName("viewDidLoad"),
            reinterpret_cast<IMP>(_I_AppViewController_viewDidLoad),
            "v@:");
        assert(res != NO);

        res = class_addMethod(
            class_AppViewController,
            sel_registerName("setRepresentedObject:"),
            reinterpret_cast<IMP>(_I_AppViewController_setRepresentedObject_),
            "v@:@");
        assert(res != NO);
    }

    struct objc_object *controller = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        class_AppViewController,
        sel_registerName("alloc"));

    controller = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *, struct objc_object *, struct objc_object *)>(objc_msgSend)(
        controller,
        sel_registerName("initWithNibName:bundle:"),
        NULL,
        NULL);

    struct objc_object *view = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *)>(objc_msgSend)(controller, sel_registerName("view"));

    struct objc_object *contentview = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *)>(objc_msgSend)(window, sel_registerName("contentView"));

    assert(sizeof(NSRect) != 1 && sizeof(NSRect) != 2 && sizeof(NSRect) != 4 && sizeof(NSRect) != 8);
    NSRect bounds = reinterpret_cast<NSRect (*)(struct objc_object *, struct objc_selector *)>(objc_msgSend_stret)(contentview, sel_registerName("bounds"));

    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, NSRect)>(objc_msgSend)(
        view,
        sel_registerName("setFrame:"),
        bounds);

    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, struct objc_object *)>(objc_msgSend)(
        window,
        sel_registerName("setContentViewController:"),
        controller);

    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, struct objc_object *)>(objc_msgSend)(
        window,
        sel_registerName("makeKeyAndOrderFront:"),
        NULL);
}

static void _I_AppDelegate_applicationWillTerminate_(struct objc_object *self, struct objc_selector *_cmd, struct objc_object *aNotification)
{
}

static void _I_AppViewController_loadView(struct objc_object *self, struct objc_selector *_cmd)
{
    struct objc_object *nsview = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        objc_getClass("NSView"),
        sel_registerName("alloc"));

    reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, struct objc_object *)>(objc_msgSend)(
        self,
        sel_registerName("setView:"),
        nsview);
}

static void _I_AppViewController_viewDidLoad(struct objc_object *self, struct objc_selector *_cmd)
{
    struct objc_super super = {self, class_getSuperclass(object_getClass(self))};
    reinterpret_cast<void (*)(struct objc_super *, struct objc_selector *)>(objc_msgSendSuper)(&super, _cmd);
}

static void _I_AppViewController_setRepresentedObject_(struct objc_object *self, struct objc_selector *_cmd, struct objc_object *representedObject)
{
    struct objc_super super = {self, class_getSuperclass(object_getClass(self))};
    reinterpret_cast<void (*)(struct objc_super *, struct objc_selector *, struct objc_object *)>(objc_msgSendSuper)(&super, _cmd, representedObject);
}

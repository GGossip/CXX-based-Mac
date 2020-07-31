#include "../AppKit/NSApplication.h"
#include "../AppKit/NSApplication_Impl.h"

#include <TargetConditionals.h>
#if TARGET_OS_IOS
#include <objc/message.h>
#include <objc/runtime.h>
#elif TARGET_OS_OSX
#include <objc/objc-runtime.h>
#else
#error Unknown Target
#endif

#include <assert.h>

struct NSViewController_Class *__attribute__((availability(macos, introduced = 10.5))) NSViewController_allocClass(
    char const *classname,
    void (*_I_NSViewController_loadView)(struct NSViewController *self, struct NSViewController_loadView *),
    void (*_I_NSViewController_viewDidLoad)(struct NSViewController *self, struct NSViewController_viewDidLoad *),
    void (*_I_NSViewController_setRepresentedObject_)(struct NSViewController *self, struct NSViewController_setRepresentedObject_ *, void *representedObject))
{
    Class class_NSViewController_CXX = objc_allocateClassPair(
        objc_getClass("NSViewController"),
        classname,
        0);
    assert(class_NSViewController_CXX != NULL);

    BOOL result1 = class_addMethod(
        class_NSViewController_CXX,
        sel_registerName("loadView"),
        reinterpret_cast<IMP>(_I_NSViewController_loadView),
        "v@:");
    assert(result1 != NO);

    BOOL result2 = class_addMethod(
        class_NSViewController_CXX,
        sel_registerName("viewDidLoad"),
        reinterpret_cast<IMP>(_I_NSViewController_viewDidLoad),
        "v@:");
    assert(result2 != NO);

    BOOL result3 = class_addMethod(
        class_NSViewController_CXX,
        sel_registerName("setRepresentedObject:"),
        reinterpret_cast<IMP>(_I_NSViewController_setRepresentedObject_),
        "v@:@");
    assert(result3 != NO);

    return reinterpret_cast<struct NSViewController_Class *>(class_NSViewController_CXX);
}

bool NSViewController_Class_addIvarVoidPointer(struct NSViewController_Class *self, char const *ivarname)
{
    BOOL result = class_addIvar(
        reinterpret_cast<Class>(self),
        ivarname,
        sizeof(void *),
        alignof(void *),
        "^v");
    return (result != NO) ? true : false;
}

struct NSViewController *NSViewController_alloc(struct NSViewController_Class *class_NSViewController_CXX)
{
    struct objc_object *viewcontroller = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        reinterpret_cast<Class>(class_NSViewController_CXX),
        sel_registerName("alloc"));

    return static_cast<struct NSViewController *>(viewcontroller);
}

struct NSViewController *NSViewController_initWithNibName(struct NSViewController *self, void *nibNameOrNil, void *nibBundleOrNil)
{
    struct objc_object *viewcontroller = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *, struct objc_object *, struct objc_object *)>(objc_msgSend)(
        self,
        sel_registerName("initWithNibName:bundle:"),
        reinterpret_cast<struct objc_object *>(nibNameOrNil),
        reinterpret_cast<struct objc_object *>(nibBundleOrNil));

    return static_cast<struct NSViewController *>(viewcontroller);
}

void NSViewController_setIvarVoidPointer(struct NSViewController *self, char const *ivarname, void *pVoid)
{
    Ivar ivar_pUserData = class_getInstanceVariable(object_getClass(self), ivarname);
    assert(ivar_pUserData != NULL);
    assert(strcmp(ivar_getTypeEncoding(ivar_pUserData), "^v") == 0);
    (*reinterpret_cast<void **>(reinterpret_cast<uintptr_t>(self) + ivar_getOffset(ivar_pUserData))) = pVoid;
}

void *NSViewController_getIvarVoidPointer(struct NSViewController *self, char const *ivarname)
{
    Ivar ivar_pUserData = class_getInstanceVariable(object_getClass(self), ivarname);
    assert(ivar_pUserData != NULL);
    assert(strcmp(ivar_getTypeEncoding(ivar_pUserData), "^v") == 0);
    return (*reinterpret_cast<void **>(reinterpret_cast<uintptr_t>(self) + ivar_getOffset(ivar_pUserData)));
}

void NSViewController_setView(struct NSViewController *self, NSView *view)
{
    return reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, struct objc_object *)>(objc_msgSend)(
        self,
        sel_registerName("setView:"),
        view);
}

void NSViewController_super_viewDidLoad(struct NSViewController *self, struct NSViewController_viewDidLoad *_cmd)
{
    struct objc_super super = {
        self,
        class_getSuperclass(object_getClass(self))};

    return reinterpret_cast<void (*)(struct objc_super *, struct objc_selector *)>(objc_msgSendSuper)(
        &super,
        reinterpret_cast<struct objc_selector *>(_cmd));
}

void NSViewController_super_setRepresentedObject_(struct NSViewController *self, struct NSViewController_setRepresentedObject_ *_cmd, void *representedObject)
{
    struct objc_super super = {
        self,
        class_getSuperclass(object_getClass(self))};

    return reinterpret_cast<void (*)(struct objc_super *, struct objc_selector *, struct objc_object *)>(objc_msgSendSuper)(
        &super,
        reinterpret_cast<struct objc_selector *>(_cmd),
        reinterpret_cast<struct objc_object *>(representedObject));
}

struct NSApplication *NSApplication_sharedApplication()
{
    struct objc_object *_application = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        objc_getClass("NSApplication"),
        sel_registerName("sharedApplication"));

    return static_cast<struct NSApplication *>(_application);
}

struct NSApplicationDelegate_Class *NSApplicationDelegate_allocClass(
    char const *classname,
    void (*_I_NSApplicationDelegate_applicationDidFinishLaunching_)(struct NSApplicationDelegate *, struct NSApplicationDelegate_applicationDidFinishLaunching_ *, void *aNotification),
    void (*_I_NSApplicationDelegate_applicationWillTerminate_)(struct NSApplicationDelegate *, struct NSApplicationDelegate_applicationWillTerminate_ *, void *aNotification),
    int8_t (*_I_NSApplicationDelegate_applicationShouldTerminateAfterLastWindowClosed_)(struct NSApplicationDelegate *, struct NSApplicationDelegate_applicationShouldTerminateAfterLastWindowClosed_ *, struct NSApplication *sender))

{
    Class class_NSApplicationDelegate_CXX;

    //objc_object *protocol_NSApplicationDelegate = objc_getProtocol("NSApplicationDelegate");
    //return NULL why???
    class_NSApplicationDelegate_CXX = objc_allocateClassPair(
        objc_getClass("NSObject"),
        classname,
        0);
    assert(class_NSApplicationDelegate_CXX != NULL);

    BOOL result1 = class_addMethod(
        class_NSApplicationDelegate_CXX,
        sel_registerName("applicationDidFinishLaunching:"),
        reinterpret_cast<IMP>(_I_NSApplicationDelegate_applicationDidFinishLaunching_),
        "v@:@");
    assert(result1 != NO);

    BOOL result2 = class_addMethod(
        class_NSApplicationDelegate_CXX,
        sel_registerName("applicationWillTerminate:"),
        reinterpret_cast<IMP>(_I_NSApplicationDelegate_applicationWillTerminate_),
        "v@:@");
    assert(result2 != NO);

    BOOL result3 = class_addMethod(
        class_NSApplicationDelegate_CXX,
        sel_registerName("applicationShouldTerminateAfterLastWindowClosed:"),
        reinterpret_cast<IMP>(_I_NSApplicationDelegate_applicationShouldTerminateAfterLastWindowClosed_),
        "v@:@");
    assert(result3 != NO);

    //res = class_addProtocol(
    //      class_MyDelegate,
    //      protocol_NSApplicationDelegate);

    //assert(res != NO);

    //objc_registerClassPair(class_NSApplicationDelegate_CXX);

    //res = class_conformsToProtocol(class_NSApplicationDelegate_CXX, protocol_NSApplicationDelegate);
    //assert(res != NO);

    return reinterpret_cast<struct NSApplicationDelegate_Class *>(class_NSApplicationDelegate_CXX);
}

struct NSApplicationDelegate *NSApplicationDelegate_alloc(struct NSApplicationDelegate_Class *class_NSApplicationDelegate_CXX)
{
    struct objc_object *_applicationDelegate = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        reinterpret_cast<Class>(class_NSApplicationDelegate_CXX),
        sel_registerName("alloc"));

    return static_cast<struct NSApplicationDelegate *>(_applicationDelegate);
}

struct NSApplicationDelegate *NSApplicationDelegate_init(struct NSApplicationDelegate *self)
{
    struct objc_object *delegate = NSObject_init(self);
    return static_cast<struct NSApplicationDelegate *>(delegate);
}

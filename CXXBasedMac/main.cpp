#include <objc/objc.h>
#include <objc/runtime.h>
#include <objc/message.h>
#include <assert.h>

extern "C" int NSApplicationMain(int argc, const char *argv[]);

void _I_AppDelegate_applicationDidFinishLaunching_(struct objc_object *self, struct objc_selector *_cmd, struct objc_object *aNotification);

void _I_AppDelegate_applicationWillTerminate_(struct objc_object *self, struct objc_selector *_cmd, struct objc_object *aNotification);

int main(int argc, const char *argv[])
{
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

        struct objc_object *sharedApplication = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
            objc_getClass("NSApplication"),
            sel_registerName("sharedApplication"));

        reinterpret_cast<void (*)(struct objc_object *, struct objc_selector *, struct objc_object *)>(objc_msgSend)(
            sharedApplication,
            sel_registerName("setDelegate:"),
            delegate);
    }

    int result = NSApplicationMain(argc, argv);
    return result;
}

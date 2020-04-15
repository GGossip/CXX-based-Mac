#include "Headers_CXX/UIKit_CXX.h"
#include "Headers_CXX/Foundation_CXX.h"
#include "Headers_CXX/Metal_CXX.h"
#include "Headers_CXX/MetalKit_CXX.h"
#include "Headers_CXX/NSRuntime_CXX.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <new>

#include "Renderer.h"

#include <assert.h>

#include <stddef.h>

void write_assets();

int main(int argc, char *argv[])
{
    write_assets();

    //Enable MultiThreaded
    {
        // Using Autorelease Pool Blocks
        // https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/MemoryMgmt/Articles/mmAutoreleasePools.html

        void *__at_autoreleasepool_obj = objc_autoreleasePoolPush();

        struct NSThreadDetachTarget_Class *threadWrapper_Class = NSThreadDetachTarget_allocClass("NSThreadWrapper", "NSMain", [](struct NSThreadDetachTarget *, struct NSThreadDetachSelector_ *, void *argument) -> void {

        });

        struct NSThreadDetachTarget *threadWrapper = NSThreadDetachTarget_init(NSThreadDetachTarget_alloc(threadWrapper_Class));

        NSThread_detachNewThreadSelector("NSMain", threadWrapper, NULL);

        assert(NSThread_isMultiThreaded() != false);

        objc_autoreleasePoolPop(__at_autoreleasepool_obj);
    }

    {
        void *__at_autoreleasepool_obj = objc_autoreleasePoolPush();

        struct UIApplicationDelegate_Class *appdelegate_Class = UIApplicationDelegate_allocClass(
            "Appdelegate",
            [](struct UIApplicationDelegate *, struct UIApplicationDelegate_didFinishLaunchingWithOptions_ *, struct UIApplication *application, void *launchOptions) -> int8_t {
                // Override point for customization after application launch.

                struct UIScreen *mainscreen = UIScreen_mainScreen();

                CGRect rect = UIScreen_bounds(mainscreen);

                struct UIWindow *window = UIWindow_initWithFrame(UIWindow_alloc(), rect);

                struct UIViewController_Class *viewcontroller_Class = UIViewController_allocClass(
                    "ViewController",
                    [](struct UIViewController *self, struct UIViewController_loadView *) -> void {
                        struct demo *_demo = new (malloc(sizeof(struct demo))) struct demo();
                        UIViewController_setIvarVoidPointer(self, "pUserData", _demo);

                        _demo->_init();

                        MTKViewDelegate_Class *renderer_Class = MTKViewDelegate_allocClass(
                            "Renderer",
                            [](struct MTKViewDelegate *self, struct MTKViewDelegate_drawableSizeWillChange_ *, struct MTKView *view, CGSize size) -> void {
                                struct demo *_demo = static_cast<struct demo *>(MTKViewDelegate_getIvarVoidPointer(self, "pUserData"));
                                _demo->_resize(size.width, size.height);
                            },
                            [](struct MTKViewDelegate *self, struct MTKViewDelegate_drawInMTKView_ *, struct MTKView *view) -> void {
                                struct demo *_demo = static_cast<struct demo *>(MTKViewDelegate_getIvarVoidPointer(self, "pUserData"));
                                _demo->_draw(view);
                            });
                        MTKViewDelegate_Class_addIvarVoidPointer(renderer_Class, "pUserData");

                        MTKViewDelegate *renderer = MTKViewDelegate_init(MTKViewDelegate_alloc(renderer_Class));
                        MTKViewDelegate_setIvarVoidPointer(renderer, "pUserData", _demo);
                        MTKView_setDelegate(_demo->_view, renderer);

                        UIViewController_setView(self, _demo->_view);
                    },
                    [](struct UIViewController *self, struct UIViewController_viewDidLoad *_cmd) -> void {
                        UIViewController_super_viewDidLoad(self, _cmd);
                        struct demo *_demo = static_cast<struct demo *>(UIViewController_getIvarVoidPointer(self, "pUserData"));
                        void *__at_autoreleasepool_obj = objc_autoreleasePoolPush();
                        _demo->_init2();
                        objc_autoreleasePoolPop(__at_autoreleasepool_obj);
                    });
                UIViewController_Class_addIvarVoidPointer(viewcontroller_Class, "pUserData");

                struct UIViewController *viewcontroller = UIViewController_init(
                    UIViewController_alloc(viewcontroller_Class));

                UIWindow_setRootViewController(window, viewcontroller);

                UIWindow_makeKeyAndVisible(window);

                return 1;
            },
            [](struct UIApplicationDelegate *, struct UIApplicationDelegate_applicationWillResignActive_ *, struct UIApplication *application) -> void {

            },
            [](struct UIApplicationDelegate *, struct UIApplicationDelegate_applicationDidEnterBackground_ *, struct UIApplication *application) -> void {

            },
            [](struct UIApplicationDelegate *, struct UIApplicationDelegate_applicationWillEnterForeground_ *, struct UIApplication *application) -> void {

            },
            [](struct UIApplicationDelegate *, struct UIApplicationDelegate_applicationWillEnterForeground_ *, struct UIApplication *application) -> void {

            },
            [](struct UIApplicationDelegate *, struct UIApplicationDelegate_applicationWillTerminate_ *, struct UIApplication *application) -> void {

            });

        UIApplicationDelegate_registerClass(appdelegate_Class);

        objc_autoreleasePoolPop(__at_autoreleasepool_obj);
    }

    return UIApplicationMain(argc, argv, NULL, NSString_initWithUTF8String(NSString_alloc(), "Appdelegate"));
}

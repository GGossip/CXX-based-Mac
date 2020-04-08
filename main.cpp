#include "Headers_CXX/AppKit_CXX.h"
#include "Headers_CXX/Foundation_CXX.h"
#include "Headers_CXX/Metal_CXX.h"
#include "Headers_CXX/MetalKit_CXX.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <new>

#include "Renderer.h"

int main(int argc, const char *argv[])
{

    //Enable MultiThreaded
    {
        // Using Autorelease Pool Blocks
        // https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/MemoryMgmt/Articles/mmAutoreleasePools.html

        void *__at_autoreleasepool_obj = objc_autoreleasePoolPush();

        struct NSThreadDetachTarget_Class *threadWrapper_Class = NSThreadDetachTarget_allocClass("NSThreadWrapper", "NSMain", [](struct NSThreadDetachTarget *, struct NSThreadDetachSelector_ *, void *argument) -> void {

        });

        bool isMultiThreaded = NSThread_isMultiThreaded();

        struct NSThreadDetachTarget *threadWrapper = NSThreadDetachTarget_init(NSThreadDetachTarget_alloc(threadWrapper_Class));

        NSThread_detachNewThreadSelector("NSMain", threadWrapper, NULL);

        //Shall we wait return?
        isMultiThreaded = NSThread_isMultiThreaded();

        objc_autoreleasePoolPop(__at_autoreleasepool_obj);
    }

    {
        void *__at_autoreleasepool_obj = objc_autoreleasePoolPush();

        struct NSApplicationDelegate_Class *appdelegate_Class = NSApplicationDelegate_allocClass(
            "Appdelegate",
            [](struct NSApplicationDelegate *, struct NSApplicationDelegate_applicationDidFinishLaunching_ *, void *aNotification) -> void {
                NSSize windowSize = NSMakeSize(480, 480);

                struct NSScreen *mainscreen = NSScreen_mainScreen();

                NSSize screenSize = NSScreen_frame(mainscreen).size;

                NSRect rect = NSMakeRect(screenSize.width / 2 - windowSize.width / 2,
                                         screenSize.height / 2 - windowSize.height / 2,
                                         windowSize.width,
                                         windowSize.height);

                struct NSWindow *window = NSWindow_initWithContentRect(
                    NSWindow_alloc(),
                    rect,
                    NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable,
                    NSBackingStoreBuffered,
                    false);

                struct NSViewController_Class *viewcontroller_Class = NSViewController_allocClass(
                    "ViewController",
                    [](struct NSViewController *self, struct NSViewController_loadView *_cmd) -> void {
                        struct demo *_demo = new (malloc(sizeof(struct demo))) struct demo();
                        NSViewController_setIvarVoidPointer(self, "pUserData", _demo);

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

                        NSViewController_setView(self, _demo->_view);
                    },
                    [](struct NSViewController *self, struct NSViewController_viewDidLoad *_cmd) -> void {
                        NSViewController_super_viewDidLoad(self, _cmd);
                        struct demo *_demo = static_cast<struct demo *>(NSViewController_getIvarVoidPointer(self, "pUserData"));
                        void *__at_autoreleasepool_obj = objc_autoreleasePoolPush();
                        _demo->_init2();
                        objc_autoreleasePoolPop(__at_autoreleasepool_obj);
                    },
                    [](struct NSViewController *self, struct NSViewController_setRepresentedObject_ *_cmd, void *representedObject) -> void {
                        NSViewController_super_setRepresentedObject_(self, _cmd, representedObject);
                    });
                NSViewController_Class_addIvarVoidPointer(viewcontroller_Class, "pUserData");

                struct NSViewController *viewcontroller = NSViewController_initWithNibName(
                    NSViewController_alloc(viewcontroller_Class),
                    NULL,
                    NULL);

                NSWindow_setContentViewController(window, viewcontroller);

                NSWindow_makeKeyAndOrderFront(window, NULL);
            },
            [](struct NSApplicationDelegate *, struct NSApplicationDelegate_applicationWillTerminate_ *, void *aNotification) -> void {

            });

        struct NSApplicationDelegate *appdelegate = NSApplicationDelegate_init(NSApplicationDelegate_alloc(appdelegate_Class));

        struct NSApplication *application = NSApplication_sharedApplication();
        NSApplication_setDelegate(application, appdelegate);

        objc_autoreleasePoolPop(__at_autoreleasepool_obj);
    }

    return NSApplicationMain(argc, argv);
}

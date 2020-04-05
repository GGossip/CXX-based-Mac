#include <objc/objc.h>
#include <objc/runtime.h>
#include <objc/message.h>
#include <assert.h>

#include "CXX_AppKit.h"

void _I_AppViewController_loadView(struct NSViewController *self, struct NSViewController_loadView *_cmd);

void _I_AppViewController_viewDidLoad(struct NSViewController *self, struct NSViewController_viewDidLoad *_cmd);

void _I_AppViewController_setRepresentedObject_(struct NSViewController *self, struct NSViewController_setRepresentedObject_ *_cmd, void *representedObject);

void _I_AppDelegate_applicationDidFinishLaunching_(struct objc_object *self, struct objc_selector *_cmd, struct objc_object *aNotification)
{
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
        NO);

    struct NSViewController *viewcontroller = NSViewController_initWithNibName(
        NSViewController_alloc(
            _I_AppViewController_loadView,
            _I_AppViewController_viewDidLoad,
            _I_AppViewController_setRepresentedObject_),
        NULL,
        NULL);

    NSWindow_setContentViewController(window, viewcontroller);

    NSWindow_makeKeyAndOrderFront(window, NULL);
}

void _I_AppDelegate_applicationWillTerminate_(struct objc_object *self, struct objc_selector *_cmd, struct objc_object *aNotification)
{
}

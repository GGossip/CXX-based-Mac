#ifndef _APPKIT_CXX_H_
#define _APPKIT_CXX_H_ 1

#include "CoreGraphics_CXX.h"

//#include <objc/NSObjCRuntime.h>
#if __LP64__ || NS_BUILD_32_LIKE_64
typedef long NSInteger;
typedef unsigned long NSUInteger;
#else
typedef int NSInteger;
typedef unsigned int NSUInteger;
#endif

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

struct NSScreen *NSScreen_mainScreen();

NSRect NSScreen_frame(struct NSScreen *);

struct NSWindow *NSWindow_alloc();

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

struct NSWindow *NSWindow_initWithContentRect(struct NSWindow *self, NSRect rect, NSWindowStyleMask styleMask, NSBackingStoreType backing, bool defer);

void NSWindow_setContentViewController(struct NSWindow *self, struct NSViewController *contentViewController);

void NSWindow_makeKeyAndOrderFront(struct NSWindow *self, void *sender);

struct NSView *NSView_alloc();

struct NSView *NSView_initWithFrame(NSView *self, NSRect frameRect);

struct NSViewController *NSViewController_alloc(
    void (*_I_NSViewController_loadView)(struct NSViewController *, struct NSViewController_loadView *),
    void (*_I_NSViewController_viewDidLoad)(struct NSViewController *, struct NSViewController_viewDidLoad *),
    void (*_I_NSViewController_setRepresentedObject_)(struct NSViewController *, struct NSViewController_setRepresentedObject_ *, void *representedObject));

struct NSViewController *NSViewController_initWithNibName(struct NSViewController *self, void *nibNameOrNil, void *nibBundleOrNil);

void NSViewController_setView(struct NSViewController *self, NSView *view);

void NSViewController_super_viewDidLoad(struct NSViewController *self, struct NSViewController_viewDidLoad *);

void NSViewController_super_setRepresentedObject_(struct NSViewController *self, struct NSViewController_setRepresentedObject_ *_cmd, void *representedObject);

struct NSApplicationDelegate *NSApplicationDelegate_alloc(
    void (*_I_NSApplicationDelegate_applicationDidFinishLaunching_)(struct NSApplicationDelegate *, struct NSApplicationDelegate_applicationDidFinishLaunching_ *, void *aNotification),
    void (*_I_NSApplicationDelegate_applicationWillTerminate_)(struct NSApplicationDelegate *, struct NSApplicationDelegate_applicationWillTerminate_ *, void *aNotification));

struct NSApplication *NSApplication_sharedApplication();

void NSApplication_setDelegate(struct NSApplication *self, struct NSApplicationDelegate *delegate);

extern "C" int NSApplicationMain(int argc, const char *argv[]);

#endif
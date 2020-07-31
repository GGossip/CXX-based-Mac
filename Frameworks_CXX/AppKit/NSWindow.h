#ifndef _APPKIT_NSWINDOW_H_
#define _APPKIT_NSWINDOW_H_ 1

#include "../Foundation/NSGeometry.h"

#include "../AppKit/NSGraphics.h"

typedef NSUInteger NSWindowStyleMask;
enum
{
    NSWindowStyleMaskBorderless = 0,
    NSWindowStyleMaskTitled = 1 << 0,
    NSWindowStyleMaskClosable = 1 << 1,
    NSWindowStyleMaskMiniaturizable = 1 << 2,
    NSWindowStyleMaskResizable = 1 << 3
};

struct NSWindow * NSWindow_alloc();

struct NSWindow * NSWindow_initWithContentRect(struct NSWindow *self, NSRect rect, NSWindowStyleMask styleMask, NSBackingStoreType backing, bool defer);

void NSWindow_setContentViewController(struct NSWindow *self, struct NSViewController *contentViewController);

void NSWindow_makeKeyAndOrderFront(struct NSWindow *self, void *sender);

#endif

#ifndef _CXX_APPKIT_H_
#define _CXX_APPKIT_H_ 1

#include "CXX_CoreGraphics.h"

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

struct NSWindow *NSWindow_alloc();

struct NSWindow *NSWindow_initWithContentRect(struct NSWindow *self, NSRect rect, NSWindowStyleMask styleMask, NSBackingStoreType backing, bool defer);

void NSWindow_setContentViewController(struct NSWindow *self, void *contentViewController);

void NSWindow_makeKeyAndOrderFront(struct NSWindow *self, void *sender);

extern "C" int NSApplicationMain(int argc, const char *argv[]);

#endif
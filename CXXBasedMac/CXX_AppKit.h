#ifndef _CXX_APPKIT_H_
#define _CXX_APPKIT_H_ 1

#include "CXX_CoreGraphics.h"

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

extern "C" int NSApplicationMain(int argc, const char *argv[]);

#endif
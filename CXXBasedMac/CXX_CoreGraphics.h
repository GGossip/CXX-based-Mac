#ifndef _CXX_CORE_GRAPHICS_H_
#define _CXX_CORE_GRAPHICS_H_ 1

#include <objc/NSObjCRuntime.h>

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

#endif
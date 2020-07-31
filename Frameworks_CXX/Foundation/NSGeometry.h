#ifndef _FOUNDATION_NSGEOMETRY_H_
#define _FOUNDATION_NSGEOMETRY_H_ 1

#include "../Foundation/NSObject.h"

#include "../CoreGraphics/CGGeometry.h"

#if __LP64__ || TARGET_OS_IPHONE || NS_BUILD_32_LIKE_64

typedef CGSize NSSize;

typedef CGRect NSRect;

#define NSGEOMETRY_TYPES_SAME_AS_CGGEOMETRY_TYPES 1

#else

typedef struct _NSSize {
    CGFloat width;		/* should never be negative */
    CGFloat height;		/* should never be negative */
} NSSize;

typedef struct _NSRect {
    NSPoint origin;
    NSSize size;
} NSRect;

#endif

NS_INLINE NSSize NSMakeSize(CGFloat w, CGFloat h) {
    NSSize s;
    s.width = w;
    s.height = h;
    return s;
}

NS_INLINE NSRect NSMakeRect(CGFloat x, CGFloat y, CGFloat w, CGFloat h) {
    NSRect r;
    r.origin.x = x;
    r.origin.y = y;
    r.size.width = w;
    r.size.height = h;
    return r;
}

#endif

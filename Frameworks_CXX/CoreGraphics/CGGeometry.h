#ifndef _COREGRAPHICS_CGGEOMETRY_H_
#define _COREGRAPHICS_CGGEOMETRY_H_ 1

#include "../CoreGraphics/CGBase.h"

/* Points. */
struct
    CGPoint
{
    CGFloat x;
    CGFloat y;
};
typedef struct CGPoint CGPoint;

/* Sizes. */

struct CGSize
{
    CGFloat width;
    CGFloat height;
};
typedef struct CGSize CGSize;

/* Rectangles. */

struct CGRect
{
    CGPoint origin;
    CGSize size;
};
typedef struct CGRect CGRect;

#endif

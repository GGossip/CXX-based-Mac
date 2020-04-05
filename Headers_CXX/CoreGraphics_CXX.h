#ifndef _COREGRAPHICS_CXX_H_
#define _COREGRAPHICS_CXX_H_ 1

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

#endif
#ifndef _METALKIT_CXX_IMPL_H_
#define _METALKIT_CXX_IMPL_H_ 1

#include "NSRuntime_CXX_IMPL.h"
#include "AppKit_CXX_IMPL.h"
#include "Metal_CXX_IMPL.h"

struct MTKView : public NSView
{
    MTKView() = delete;
};

struct CAMetalDrawable : public MTLDrawable
{
    CAMetalDrawable() = delete;
};

struct MTKViewDelegate : public MTLDrawable
{
    MTKViewDelegate() = delete;
};

#endif

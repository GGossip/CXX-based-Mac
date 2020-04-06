#ifndef _METALKIT_CXX_H_
#define _METALKIT_CXX_H_ 1

#include "AppKit_CXX.h"
#include "Metal_CXX.h"

struct MTKView *MTKView_alloc();

struct MTKView *MTKView_initWithFrame(struct MTKView *self, CGRect frameRect, struct MTLDevice *device);

struct MTKViewDelegate_Class *MTKViewDelegate_allocClass(
    char const *classname,
    void (*_I_MTKViewDelegate_drawableSizeWillChange_)(struct NSApplicationDelegate *, struct MTKViewDelegate_drawableSizeWillChange_ *, struct MTKView *view, CGSize size),
    void (*_I_MTKViewDelegate_drawInMTKView_)(struct NSApplicationDelegate *, struct MTKViewDelegate_drawInMTKView_ *, struct MTKView *view));

struct MTKViewDelegate *MTKViewDelegate_alloc(struct MTKViewDelegate_Class *);

struct MTKViewDelegate *MTKViewDelegate_init(struct MTKViewDelegate *self);

void MTKView_setDelegate(struct MTKView *self, struct MTKViewDelegate *delegate);

void MTKView_setColorPixelFormat(struct MTKView *self, MTLPixelFormat colorPixelFormat);

void MTKView_setDepthStencilPixelFormat(struct MTKView *self, MTLPixelFormat depthStencilPixelFormat);

void MTKView_setSampleCount(struct MTKView *self, NSUInteger sampleCount);

struct MTLRenderPassDescriptor *MTKView_currentRenderPassDescriptor(struct MTKView *self);

struct CAMetalDrawable * MTKView_currentDrawable(struct MTKView *self);

void NSViewController_setView(struct NSViewController *self, struct MTKView *view);

void MTLCommandBuffer_presentDrawable(struct MTLCommandBuffer *self, struct CAMetalDrawable *drawable);

#endif
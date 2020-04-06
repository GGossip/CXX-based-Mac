#include "Headers_CXX/AppKit_CXX.h"
#include "Headers_CXX/MetalKit_CXX.h"

void _I_Renderer_drawableSizeWillChange_(struct NSApplicationDelegate *, struct MTKViewDelegate_drawableSizeWillChange_ *, struct MTKView *view, CGSize size);

void _I_Renderer_drawInMTKView_(struct NSApplicationDelegate *, struct MTKViewDelegate_drawInMTKView_ *, struct MTKView *view);

extern struct MTLDevice *g_device;
extern struct MTKView *g_view;
extern void demo_init(struct MTKView *view);

void _I_AppViewController_loadView(struct NSViewController *self, struct NSViewController_loadView *_cmd)
{
    NSRect rect = NSMakeRect(0, 0, 800, 600);
    g_device = MTLCreateSystemDefaultDevice();
    g_view = MTKView_initWithFrame(
        MTKView_alloc(),
        rect,
        g_device);

    MTKViewDelegate_Class *renderer_Class = MTKViewDelegate_allocClass(
        "Renderer",
        _I_Renderer_drawableSizeWillChange_,
        _I_Renderer_drawInMTKView_);

    MTKViewDelegate *renderer = MTKViewDelegate_init(MTKViewDelegate_alloc(renderer_Class));
    MTKView_setDelegate(g_view, renderer);

    NSViewController_setView(self, g_view);
}

void _I_AppViewController_viewDidLoad(struct NSViewController *self, struct NSViewController_viewDidLoad *_cmd)
{
    NSViewController_super_viewDidLoad(self, _cmd);
    demo_init(g_view);
}

void _I_AppViewController_setRepresentedObject_(struct NSViewController *self, struct NSViewController_setRepresentedObject_ *_cmd, void *representedObject)
{
    NSViewController_super_setRepresentedObject_(self, _cmd, representedObject);
}

#include "Headers_CXX/AppKit_CXX.h"
#include "Headers_CXX/MetalKit_CXX.h"

void _I_Renderer_drawableSizeWillChange_(struct NSApplicationDelegate *, struct MTKViewDelegate_drawableSizeWillChange_ *, struct MTKView *view, CGSize size);

void _I_Renderer_drawInMTKView_(struct NSApplicationDelegate *, struct MTKViewDelegate_drawInMTKView_ *, struct MTKView *view);

void _I_AppViewController_loadView(struct NSViewController *self, struct NSViewController_loadView *_cmd)
{
    NSRect rect = NSMakeRect(0, 0, 800, 600);
    MTLDevice *device = MTLCreateSystemDefaultDevice();
    struct MTKView *view = MTKView_initWithFrame(
        MTKView_alloc(),
        rect,
        device);

    MTKViewDelegate *renderer = MTKViewDelegate_alloc(
        _I_Renderer_drawableSizeWillChange_,
        _I_Renderer_drawInMTKView_);
    MTKView_setDelegate(view, renderer);

    NSViewController_setView(self, view);
}

void _I_AppViewController_viewDidLoad(struct NSViewController *self, struct NSViewController_viewDidLoad *_cmd)
{
    NSViewController_super_viewDidLoad(self, _cmd);
}

void _I_AppViewController_setRepresentedObject_(struct NSViewController *self, struct NSViewController_setRepresentedObject_ *_cmd, void *representedObject)
{
    NSViewController_super_setRepresentedObject_(self, _cmd, representedObject);
}

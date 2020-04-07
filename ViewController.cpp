#include "Headers_CXX/AppKit_CXX.h"
#include "Headers_CXX/MetalKit_CXX.h"

#include <stdlib.h>
#include <new>

void _I_Renderer_drawableSizeWillChange_(struct MTKViewDelegate *, struct MTKViewDelegate_drawableSizeWillChange_ *, struct MTKView *view, CGSize size);

void _I_Renderer_drawInMTKView_(struct MTKViewDelegate *, struct MTKViewDelegate_drawInMTKView_ *, struct MTKView *view);

#include "Renderer.h"

void _I_AppViewController_loadView(struct NSViewController *self, struct NSViewController_loadView *_cmd)
{

    struct demo *demo = new (malloc(sizeof(struct demo))) struct demo();
    demo->_init();

    MTKViewDelegate_Class *renderer_Class = MTKViewDelegate_allocClass(
        "Renderer",
        _I_Renderer_drawableSizeWillChange_,
        _I_Renderer_drawInMTKView_);

    MTKViewDelegate *renderer = MTKViewDelegate_init(MTKViewDelegate_alloc(renderer_Class));
    MTKViewDelegate_setUserData(renderer, demo);
    MTKView_setDelegate(demo->_view, renderer);

    NSViewController_setView(self, demo->_view);
}

void _I_AppViewController_viewDidLoad(struct NSViewController *self, struct NSViewController_viewDidLoad *_cmd)
{
    NSViewController_super_viewDidLoad(self, _cmd);
    //demo->_init
}

void _I_AppViewController_setRepresentedObject_(struct NSViewController *self, struct NSViewController_setRepresentedObject_ *_cmd, void *representedObject)
{
    NSViewController_super_setRepresentedObject_(self, _cmd, representedObject);
}

#include "Headers_CXX/AppKit_CXX.h"
#include "Headers_CXX/MetalKit_CXX.h"

#include <stdlib.h>
#include <new>

void _I_Renderer_drawableSizeWillChange_(struct MTKViewDelegate *, struct MTKViewDelegate_drawableSizeWillChange_ *, struct MTKView *view, CGSize size);

void _I_Renderer_drawInMTKView_(struct MTKViewDelegate *, struct MTKViewDelegate_drawInMTKView_ *, struct MTKView *view);

#include "Renderer.h"

static demo *g_demo;

void _I_AppViewController_loadView(struct NSViewController *self, struct NSViewController_loadView *_cmd)
{

    struct demo *_demo = new (malloc(sizeof(struct demo))) struct demo();
    _demo->_init();

    MTKViewDelegate_Class *renderer_Class = MTKViewDelegate_allocClass(
        "Renderer",
        [](struct MTKViewDelegate *self, struct MTKViewDelegate_drawableSizeWillChange_ *, struct MTKView *view, CGSize size) -> void {
            struct demo *_demo = static_cast<struct demo *>(MTKViewDelegate_getUserData(self));
            _demo->_resize(size.width, size.height);
        },
        [](struct MTKViewDelegate *self, struct MTKViewDelegate_drawInMTKView_ *, struct MTKView *view) -> void {
            struct demo *_demo = static_cast<struct demo *>(MTKViewDelegate_getUserData(self));
            _demo->_draw(view);
        });

    MTKViewDelegate *renderer = MTKViewDelegate_init(MTKViewDelegate_alloc(renderer_Class));
    MTKViewDelegate_setUserData(renderer, _demo);
    MTKView_setDelegate(_demo->_view, renderer);

    NSViewController_setView(self, _demo->_view);

    g_demo = _demo;
}

void _I_AppViewController_viewDidLoad(struct NSViewController *self, struct NSViewController_viewDidLoad *_cmd)
{
    NSViewController_super_viewDidLoad(self, _cmd);
    g_demo->_init2();
}

void _I_AppViewController_setRepresentedObject_(struct NSViewController *self, struct NSViewController_setRepresentedObject_ *_cmd, void *representedObject)
{
    NSViewController_super_setRepresentedObject_(self, _cmd, representedObject);
}

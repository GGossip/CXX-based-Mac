#include <objc/objc.h>
#include <objc/runtime.h>
#include <objc/message.h>

#include "CXX_AppKit.h"

void _I_AppViewController_loadView(struct NSViewController *self, struct NSViewController_loadView *_cmd)
{
    NSRect rect = NSMakeRect(0, 0, 800, 600);
    struct NSView *view = NSView_initWithFrame(
        NSView_alloc(),
        rect);

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

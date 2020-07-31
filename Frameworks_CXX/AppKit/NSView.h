#ifndef _APPKIT_NSVIEW_H_
#define _APPKIT_NSVIEW_H_ 1

#include "../Foundation/NSGeometry.h"

struct NSView *NSView_alloc();

struct NSView *NSView_initWithFrame(NSView *self, NSRect frameRect);

#endif
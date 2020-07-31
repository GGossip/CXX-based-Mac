#ifndef _APPKIT_NSSCREEN_H_
#define _APPKIT_NSSCREEN_H_ 1

#include "../Foundation/NSGeometry.h"

struct NSScreen *NSScreen_mainScreen();

NSRect NSScreen_frame(struct NSScreen *self);

#endif
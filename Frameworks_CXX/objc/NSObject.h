#ifndef _OBJC_NSOBJECT_H_
#define _OBJC_NSOBJECT_H_ 1

#include "../objc/NSObjCRuntime.h"

struct NSObject *NSObject_init(struct NSObject *self);
void NSObject_release(struct NSObject *self);
NSUInteger NSObject_retainCount(struct NSObject *self);

#endif
#ifndef _NSRUNTIME_CXX_H_
#define _NSRUNTIME_CXX_H_ 1

//#include <objc/NSObjCRuntime.h>
#if __LP64__ || NS_BUILD_32_LIKE_64
typedef long NSInteger;
typedef unsigned long NSUInteger;
#else
typedef int NSInteger;
typedef unsigned int NSUInteger;
#endif

void NSObject_release(struct NSObject *self);
NSUInteger NSObject_retainCount(struct NSObject *self);

struct NSString *NSString_stringWithUTF8String(char const *nullTerminatedCString);
void NSString_release(struct NSString *self);
NSUInteger NSString_retainCount(struct NSString *self);

#endif
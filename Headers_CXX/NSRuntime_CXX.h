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

#endif
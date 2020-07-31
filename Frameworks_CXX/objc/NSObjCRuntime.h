#ifndef _OBJC_NSOBJCRUNTIME_H_
#define _OBJC_NSOBJCRUNTIME_H_ 1

#if __LP64__ || 0 || NS_BUILD_32_LIKE_64
typedef long NSInteger;
typedef unsigned long NSUInteger;
#else
typedef int NSInteger;
typedef unsigned int NSUInteger;
#endif

#endif

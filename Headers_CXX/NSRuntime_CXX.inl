
#ifndef _NSRUNTIME_CXX_INL_
#define _NSRUNTIME_CXX_INL_ 1

#include <objc/objc.h>

struct NSObject : public objc_object
{
    NSObject() = delete;
};

struct NSString : public NSObject
{
    NSString() = delete;
};

#endif
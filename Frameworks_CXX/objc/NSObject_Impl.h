#ifndef _OBJC_NSOBJECT_IMPL_H_
#define _OBJC_NSOBJECT_IMPL_H_ 1

struct NSObject : public struct objc_object
{
    NSObject() = delete;
};


struct NSString : public NSObject
{
    NSString() = delete;
};

#endif
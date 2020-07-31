#ifndef _APPKIT_NSAPPLICATION_IMPL_H_
#define _APPKIT_NSAPPLICATION_IMPL_H_ 1

struct NSApplication : public NSObject
{
    NSApplication() = delete;
};

struct NSApplicationDelegate_Class : struct objc_class
{
    NSApplicationDelegate_Class() = delete;
};

struct NSApplicationDelegate : public NSObject
{
    NSApplicationDelegate() = delete;
};

#endif
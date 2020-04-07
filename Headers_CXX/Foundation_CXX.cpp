#include "Foundation_CXX.h"
#include "Foundation_CXX_IMPL.h"

#include <objc/objc.h>
#include <objc/objc-runtime.h>

struct NSObject *NSArrayNSObject_objectAtIndexedSubscript(struct NSArrayNSObject *self, NSUInteger idx)
{
    struct objc_object *object = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *, NSUInteger)>(objc_msgSend)(
        self,
        sel_registerName("objectAtIndexedSubscript:"),
        idx);
    return static_cast<struct NSObject *>(object);
}

struct NSFileManager *NSFileManager_defaultManager()
{
    struct objc_object *fileManager = reinterpret_cast<struct objc_object *(*)(Class, struct objc_selector *)>(objc_msgSend)(
        objc_getClass("NSFileManager"),
        sel_registerName("defaultManager"));
    return static_cast<struct NSFileManager *>(fileManager);
}

struct NSArrayNSURL *NSFileManager_URLsForDirectory(struct NSFileManager *self, NSSearchPathDirectory inDomains, NSSearchPathDomainMask domainMask)
{
    struct objc_object *arrayurl = reinterpret_cast<struct objc_object *(*)(struct objc_object *, struct objc_selector *, NSSearchPathDirectory, NSSearchPathDomainMask)>(objc_msgSend)(
        self,
        sel_registerName("URLsForDirectory:inDomains:"),
        inDomains,
        domainMask);

    return static_cast<struct NSArrayNSURL *>(arrayurl);
}

struct NSURL *NSArrayNSURL_objectAtIndexedSubscript(struct NSArrayNSURL *self, NSUInteger idx)
{
    NSObject *url = NSArrayNSObject_objectAtIndexedSubscript(self, idx);
    return static_cast<struct NSURL *>(url);
}

char const *NSURL_fileSystemRepresentation(struct NSURL *self)
{
    char const *filename = reinterpret_cast<char const *(*)(struct objc_object *, struct objc_selector *)>(objc_msgSend)(
        self,
        sel_registerName("fileSystemRepresentation"));
    return filename;
}
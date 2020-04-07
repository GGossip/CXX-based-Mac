#include "Headers_CXX/AppKit_CXX.h"
#include "Headers_CXX/Foundation_CXX.h"

#include <stddef.h>

void _I_AppDelegate_applicationDidFinishLaunching_(struct NSApplicationDelegate *, struct NSApplicationDelegate_applicationDidFinishLaunching_ *, void *aNotification);

void _I_AppDelegate_applicationWillTerminate_(struct NSApplicationDelegate *, struct NSApplicationDelegate_applicationWillTerminate_ *, void *aNotification);

int main(int argc, const char *argv[])
{

    //Enable MultiThreaded
    {
        // Using Autorelease Pool Blocks
        // https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/MemoryMgmt/Articles/mmAutoreleasePools.html

        void *__at_autoreleasepool_obj = objc_autoreleasePoolPush();

        struct NSThreadDetachTarget_Class *threadWrapper_Class = NSThreadDetachTarget_allocClass("NSThreadWrapper", "NSMain", [](struct NSThreadDetachTarget *, struct NSThreadDetachSelector_ *, void *argument) -> void {

        });

        bool isMultiThreaded = NSThread_isMultiThreaded();

        struct NSThreadDetachTarget *threadWrapper = NSThreadDetachTarget_init(NSThreadDetachTarget_alloc(threadWrapper_Class));

        NSThread_detachNewThreadSelector("NSMain", threadWrapper, NULL);

        //Shall we wait return?
        isMultiThreaded = NSThread_isMultiThreaded();

        objc_autoreleasePoolPop(__at_autoreleasepool_obj);
    }

    {
        void *__at_autoreleasepool_obj = objc_autoreleasePoolPush();

        char const *filename = NSURL_fileSystemRepresentation(NSArrayNSURL_objectAtIndexedSubscript(
            NSFileManager_URLsForDirectory(NSFileManager_defaultManager(), NSCachesDirectory, NSUserDomainMask),
            0));

        objc_autoreleasePoolPop(__at_autoreleasepool_obj);
    }

    {
        void *__at_autoreleasepool_obj = objc_autoreleasePoolPush();

        struct NSApplicationDelegate_Class *appdelegate_Class = NSApplicationDelegate_allocClass(
            "Appdelegate",
            _I_AppDelegate_applicationDidFinishLaunching_,
            _I_AppDelegate_applicationWillTerminate_);

        struct NSApplicationDelegate *appdelegate = NSApplicationDelegate_init(NSApplicationDelegate_alloc(appdelegate_Class));

        struct NSApplication *application = NSApplication_sharedApplication();
        NSApplication_setDelegate(application, appdelegate);

        objc_autoreleasePoolPop(__at_autoreleasepool_obj);
    }

    return NSApplicationMain(argc, argv);
}

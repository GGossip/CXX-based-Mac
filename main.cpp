#include "Headers_CXX/AppKit_CXX.h"
#include "Headers_CXX/Foundation_CXX.h"

void _I_AppDelegate_applicationDidFinishLaunching_(struct NSApplicationDelegate *, struct NSApplicationDelegate_applicationDidFinishLaunching_ *, void *aNotification);

void _I_AppDelegate_applicationWillTerminate_(struct NSApplicationDelegate *, struct NSApplicationDelegate_applicationWillTerminate_ *, void *aNotification);

int main(int argc, const char *argv[])
{
    {
        char const *filename = NSURL_fileSystemRepresentation(NSArrayNSURL_objectAtIndexedSubscript(
            NSFileManager_URLsForDirectory(NSFileManager_defaultManager(), NSCachesDirectory, NSUserDomainMask),
            0));

        //autoreleasepool
    }

    {
        struct NSApplicationDelegate_Class *appdelegate_Class = NSApplicationDelegate_allocClass(
            "Appdelegate",
            _I_AppDelegate_applicationDidFinishLaunching_,
            _I_AppDelegate_applicationWillTerminate_);

        struct NSApplicationDelegate *appdelegate = NSApplicationDelegate_init(NSApplicationDelegate_alloc(appdelegate_Class));

        struct NSApplication *application = NSApplication_sharedApplication();
        NSApplication_setDelegate(application, appdelegate);
    }

    return NSApplicationMain(argc, argv);
}

#include "Headers_CXX/AppKit_CXX.h"

void _I_AppDelegate_applicationDidFinishLaunching_(struct NSApplicationDelegate *, struct NSApplicationDelegate_applicationDidFinishLaunching_ *, void *aNotification);

void _I_AppDelegate_applicationWillTerminate_(struct NSApplicationDelegate *, struct NSApplicationDelegate_applicationWillTerminate_ *, void *aNotification);

int main(int argc, const char *argv[])
{
    {
        struct NSApplicationDelegate *appdelegate = NSApplicationDelegate_alloc(
            _I_AppDelegate_applicationDidFinishLaunching_,
            _I_AppDelegate_applicationWillTerminate_);

        struct NSApplication *application = NSApplication_sharedApplication();
        NSApplication_setDelegate(application, appdelegate);
    }

    return NSApplicationMain(argc, argv);
}

#ifndef _APPKIT_NSAPPLICATION_H_
#define _APPKIT_NSAPPLICATION_H_ 1

#include "../Foundation/NSObject.h"

struct NSViewController_Class *__attribute__((availability(macos, introduced = 10.5))) NSViewController_allocClass(
    char const *classname,
    void (*_I_NSViewController_loadView)(struct NSViewController *self, struct NSViewController_loadView *),
    void (*_I_NSViewController_viewDidLoad)(struct NSViewController *self, struct NSViewController_viewDidLoad *),
    void (*_I_NSViewController_setRepresentedObject_)(struct NSViewController *self, struct NSViewController_setRepresentedObject_ *, void *representedObject));

bool __attribute__((availability(macos, introduced = 10.5))) NSViewController_Class_addIvarVoidPointer(struct NSViewController_Class *self, char const *ivarname);

struct NSViewController *__attribute__((availability(macos, introduced = 10.5))) NSViewController_alloc(struct NSViewController_Class *);

struct NSViewController *__attribute__((availability(macos, introduced = 10.5))) NSViewController_initWithNibName(struct NSViewController *self, void *nibNameOrNil, void *nibBundleOrNil);

void __attribute__((availability(macos, introduced = 10.5))) NSViewController_setIvarVoidPointer(struct NSViewController *self, char const *ivarname, void *pVoid);

void *__attribute__((availability(macos, introduced = 10.5))) NSViewController_getIvarVoidPointer(struct NSViewController *self, char const *ivarname);

void __attribute__((availability(macos, introduced = 10.5))) NSViewController_setView(struct NSViewController *self, struct NSView *view);

void __attribute__((availability(macos, introduced = 10.5))) NSViewController_super_viewDidLoad(struct NSViewController *self, struct NSViewController_viewDidLoad *);

void __attribute__((availability(macos, introduced = 10.5))) NSViewController_super_setRepresentedObject_(struct NSViewController *self, struct NSViewController_setRepresentedObject_ *, void *representedObject);

struct NSApplication *NSApplication_sharedApplication();

struct NSApplicationDelegate_Class *NSApplicationDelegate_allocClass(
    char const *classname,
    void (*_I_NSApplicationDelegate_applicationDidFinishLaunching_)(struct NSApplicationDelegate *, struct NSApplicationDelegate_applicationDidFinishLaunching_ *, void *aNotification),
    void (*_I_NSApplicationDelegate_applicationWillTerminate_)(struct NSApplicationDelegate *, struct NSApplicationDelegate_applicationWillTerminate_ *, void *aNotification),
    int8_t (*_I_NSApplicationDelegate_applicationShouldTerminateAfterLastWindowClosed_)(struct NSApplicationDelegate *, struct NSApplicationDelegate_applicationShouldTerminateAfterLastWindowClosed_ *, struct NSApplication *sender));

struct NSApplicationDelegate *NSApplicationDelegate_alloc(struct NSApplicationDelegate_Class *);

struct NSApplicationDelegate *NSApplicationDelegate_init(struct NSApplicationDelegate *self);

extern "C" int NSApplicationMain(int argc, const char *argv[]);

#endif
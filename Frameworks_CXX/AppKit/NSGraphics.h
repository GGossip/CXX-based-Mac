#ifndef _APPKIT_NSGRAPHICS_H_
#define _APPKIT_NSGRAPHICS_H_ 1

#include "../Foundation/NSGeometry.h"

typedef NSUInteger NSBackingStoreType;
enum
{

    NSBackingStoreRetained __attribute__((availability(macos, introduced = 10.0, deprecated = 10.13, replacement = "NSBackingStoreBuffered"))) = 0,
    NSBackingStoreNonretained __attribute__((availability(macos, introduced = 10.0, deprecated = 10.13, replacement = "NSBackingStoreBuffered"))) = 1,
    NSBackingStoreBuffered = 2,
};

#endif
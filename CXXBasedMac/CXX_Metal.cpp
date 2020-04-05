#include "CXX_Metal.h"

#include <objc/objc.h>

extern "C" struct objc_object * MTLCreateSystemDefaultDevice(void);

struct MTLDevice * CXX_MTLCreateSystemDefaultDevice()
{
    return reinterpret_cast<struct MTLDevice *>(MTLCreateSystemDefaultDevice());
}

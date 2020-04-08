#include "Dispatch_CXX.h"
#include "Dispatch_CXX_IMPL.h"

#include <objc/objc.h>
#include <objc/objc-runtime.h>

extern "C" void dispatch_release(struct objc_object *object);

void dispatch_release(dispatch_object_t object)
{
    return dispatch_release(static_cast<struct objc_object *>(object));
}

extern "C" struct dispatch_queue_s _dispatch_main_q;

dispatch_queue_main_t dispatch_get_main_queue(void)
{
    return reinterpret_cast<dispatch_queue_main_t>(&_dispatch_main_q);
}

struct __block_literal_dispatch_block_t
{
    void *isa;
    int flags;
    int reserved;
    void (*invoke)(struct __block_literal_dispatch_block_t *);
    struct __block_descriptor_dispatch_block_t *descriptor;
    void *buffer;
    void (*pfnCallback)(void *buffer);
};

static void __block_invoke_dispatch_block_t(struct __block_literal_dispatch_block_t *_block)
{
    _block->pfnCallback(_block->buffer);
}

static struct __block_descriptor_dispatch_block_t
{
    unsigned long int reserved;
    unsigned long int Block_size;
} __block_descriptor_dispatch_block_t = {0, sizeof(struct __block_literal_dispatch_block_t)};

extern "C" dispatch_data_t dispatch_data_create(void const *buffer, size_t size, struct objc_object *queue, struct objc_object *destructor);

dispatch_data_t dispatch_data_create(void *buffer, size_t size, dispatch_queue_t queue, void (*pfnCallback)(void *buffer))
{
    struct __block_literal_dispatch_block_t __block_literal_dispatch_block_t = {
        &_NSConcreteStackBlock,
        BLOCK_HAS_STRET,
        0, // uninitialized
        __block_invoke_dispatch_block_t,
        &__block_descriptor_dispatch_block_t,
        buffer,
        pfnCallback};
    return dispatch_data_create(buffer, size, queue, reinterpret_cast<struct objc_object *>(&__block_literal_dispatch_block_t));
}

dispatch_data_t dispatch_data_create(void *buffer, size_t size, dispatch_queue_main_t queue, void (*pfnCallback)(void *buffer))
{
    return dispatch_data_create(buffer, size, static_cast<dispatch_queue_t>(queue), pfnCallback);
}

void dispatch_release(dispatch_data_t object)
{
    return dispatch_release(static_cast<dispatch_object_t>(object));
}
#ifndef _DISPATCH_QUEUE_H_
#define _DISPATCH_QUEUE_H_ 1

DISPATCH_DECL(dispatch_queue);

DISPATCH_DECL_SUBCLASS(dispatch_queue_global, dispatch_queue);

DISPATCH_EXPORT struct dispatch_queue_s __attribute__((availability(ios, introduced=4.0), availability(macos, introduced = 10.6))) _dispatch_main_q;

DISPATCH_INLINE DISPATCH_ALWAYS_INLINE DISPATCH_CONST DISPATCH_NOTHROW dispatch_queue_main_t dispatch_get_main_queue(void)
{
	return DISPATCH_GLOBAL_OBJECT(dispatch_queue_main_t, _dispatch_main_q);
}

#endif
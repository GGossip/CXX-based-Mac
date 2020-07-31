#ifndef _DISPATCH_DATA_H_
#define _DISPATCH_DATA_H_ 1

DISPATCH_DATA_DECL(dispatch_data);

dispatch_data_t dispatch_data_create(void *buffer, size_t size, dispatch_queue_t queue, void *pUserData, void (*pfnCallback)(void *pUserData, void *buffer));

#endif
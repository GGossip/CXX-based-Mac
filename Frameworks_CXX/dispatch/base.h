#ifndef _DISPATCH_BASE_H_
#define _DISPATCH_BASE_H_ 1

#define DISPATCH_NOTHROW __attribute__((__nothrow__))

#define DISPATCH_NONNULL_ALL __attribute__((__nonnull__))

#define DISPATCH_CONST __attribute__((__const__))

#define DISPATCH_WARN_RESULT __attribute__((__warn_unused_result__))

#define DISPATCH_ALWAYS_INLINE __attribute__((__always_inline__))

#define DISPATCH_EXPORT extern __attribute__((visibility("default")))

#define DISPATCH_INLINE static __inline__

#ifndef _Nullable
#define _Nullable
#endif

#endif
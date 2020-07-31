#ifndef _DISPATCH_OBJECT_H_
#define _DISPATCH_OBJECT_H_ 1

typedef struct dispatch_object_s
{
private:
    dispatch_object_s();
    ~dispatch_object_s();
    dispatch_object_s(const dispatch_object_s &);
    void operator=(const dispatch_object_s &);
} * dispatch_object_t;
#define DISPATCH_DECL(name) \
    typedef struct name##_s : public dispatch_object_s{} * name##_t
#define DISPATCH_DECL_SUBCLASS(name, base) \
    typedef struct name##_s : public base##_s{} * name##_t
#define DISPATCH_GLOBAL_OBJECT(type, object) (static_cast<type>(&(object)))
#define DISPATCH_RETURNS_RETAINED

#define DISPATCH_DATA_DECL(name) DISPATCH_DECL(name)

DISPATCH_EXPORT DISPATCH_NONNULL_ALL DISPATCH_NOTHROW void __attribute__((availability(ios, introduced = 4.0), availability(macos, introduced = 10.6))) dispatch_release(dispatch_object_t object);

#endif